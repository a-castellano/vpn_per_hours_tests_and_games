from BaseHTTPServer import BaseHTTPRequestHandler
import urlparse
import MySQLdb
from time import sleep
import os
import subprocess
import digitalocean
import route53
import random
import threading  

conn = route53.connect(
    aws_access_key_id='AKIAIRXB2NBW6JBJSMRQ',
    aws_secret_access_key='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',
)

APIToken = '82bede0e660f5872d5988a4785fa6a10aa8f55cb7e52882906ca89c1b6a2c773'
sshKeyList = [
    "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQD04ZoHu9qszy61gVeggjYiR/KLdZrFOpT6qiULOj1xc4ZX6TuHLFE1WklzYjRhqukVNPRlsg3lxG8yBOxSQmAmKYQgJr2lA0JqORpRWWodDqKp7a0WKuaur6UJeTSqUUrOJq/hktUcTLlD3x5miumx1g8+QjkSi4zVe4UXenv8fnddcZJD8LxU6aNJzDmlEDw/3YjADdUhxTS6n95WfoRPD9oS96BlEIBNhsSZExtchs84CNR/g8Rp+QxchySQ/nqaJO6yHBKK/ZUFySQYwg+UfRPxWK9z8JV+VFrWVKZSJ7qiuWCnr9R4IMMLhKhpwFUuqqO57AZghQY4JyQ5XUxh root@Paula"]

''''
0 -> USA
1 -> Germany
2 -> Singapore
3 -> UK
4 -> Amsterdam
5 -> Canada
'''
providers = ['DigitalOcean', 'vultr']

zones = {
    0: {'DigitalOcean': ['nyc1', 'nyc2', 'nyc3', 'sfo1']},
    1: {'DigitalOcean': ['fra1']},
    2: {'DigitalOcean': ['sgp1']},
    3: {'DigitalOcean': ['lon1']},
    4: {'DigitalOcean': ['ams2', 'ams3']},
    5: {'DigitalOcean': ['tor1']}
}

zoneNames = [
    'usa',
    'ger',
    'sgp',
    'uk',
    'ams',
    'can'
]

db_host = 'kafir.es'
user = 'vpn'
password = 'XLRc3H1y4Db0G4qR630Qk2xPF3D88P'
database = 'vpn'
db = MySQLdb.connect(host=db_host, user=user, passwd=password, db=database)

def getUsername(userId):
    cursor = db.cursor()
    query = ("SELECT username FROM users WHERE id={};".format(userId))
    cursor.execute(query)
    data = cursor.fetchone()
    cursor.close()
    # userId and zone
    return data[0]


def pointIP(url, ip):
    print "Apuntamos la maquina"
    conn = route53.connect(
        aws_access_key_id='AKIAIRXB2NBW6JBJSMRQ',
        aws_secret_access_key='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',
    )

    zone = conn.get_hosted_zone_by_id('ZPEB3E12BAWA8')
    name_to_match = url + '.'

    encontrado = False
    for record_set in zone.record_sets:
        print(record_set.name)
        if record_set.name == name_to_match:
            encontrado = True
            # De momento hago un update porque pueden existir dos urls iguales
            record_set.delete()
            print "Borrado"
            new_record, change_info = zone.create_a_record(name=name_to_match, values=[str(ip)], )
            break;

    if not encontrado:
        print "Lo creamos"
        new_record, change_info = zone.create_a_record(name=name_to_match, values=[str(ip)], )


def getInfoFromToken(token):
    cursor = db.cursor()
    query = ("SELECT user_id, zone FROM servers WHERE token='{}';".format(token))
    cursor.execute(query)
    serverToCreate = cursor.fetchone()
    cursor.close()
    # machineId and zone
    if serverToCreate:
        return serverToCreate[0], serverToCreate[1]
    else:
        return None, None


def createDropletDigitalOcean(url, region):
    manager = digitalocean.Manager(token=APIToken)
    droplet = digitalocean.Droplet(token=APIToken,
                                   name=url,
                                   region=region,  # New York 2
                                   image='ubuntu-14-04-x64',  # Ubuntu 14.04 x64
                                   ssh_keys=sshKeyList,
                                   size_slug='512mb',  # 512MB
                                   backups=False)
    droplet.create()
    print "Creado"
    dropletID = str(droplet).split(' ')[0]
    print dropletID
    sleep(10)
    dropletData = manager.get_droplet(dropletID)
    ip = dropletData.ip_address
    pointIP(url, ip)
    sleep(30)
    # ip = dropletData.ip_address
    return ip,dropletID


def setUpVPNServer(userId,token,url,dropletID,ip):
    cursor = db.cursor()
    query = ("SELECT name, password FROM vpnusers WHERE user_id={};".format(userId))
    cursor.execute(query)
    users = cursor.fetchall()
    cursor = db.cursor()
    update_query = ("UPDATE servers SET status='Installing VPN server.'  WHERE token='{}';".format(token))
    cursor.execute(update_query)
    db.commit()
    cursor.close()

    userfile = open("../ansible/files/secrets/"+url,'w')
    index=210
    for user in users:
        userfile.write(user[0]+'\t*\t'+user[1]+'\t*\t192.168.155.'+str(index)+'\n')
        index += 1
    userfile.close()

    inventoryfile = open("../ansible/inventories/"+url,'w')
    inventoryfile.write('[target]\n{}\n'.format(ip))
    inventoryfile.close()

    print "Lanzamos script de instalacion (ansible)"
    subprocess.check_call('/usr/bin/ansible-playbook ../ansible/pptp_setup.yml -i ../ansible/inventories/{} -e "secrets_file={}"'.format(url,url), shell=True)
    


def createDroplet(zone, userId, token):
    zoneinfo = zones[zone]
    candidateProviders = []
    for provider in providers:
        if provider in zoneinfo:
            candidateProviders.append(provider)
    provider = candidateProviders[random.randint(0, len(candidateProviders) - 1)]
    regions = zoneinfo[provider]
    region = regions[random.randint(0, len(regions) - 1)]
    username = getUsername(userId)
    url = zoneNames[zone] + '.' + username + '.vpn.windmaker.net'
    cursor = db.cursor()
    query = ("SELECT name FROM servers WHERE user_id={};".format(userId))
    cursor.execute(query)
    results = cursor.fetchall()
    cursor = db.cursor()
    usedURLS = []
    for r in results:
         usedURLS.append(r[0])
    counter = 1
    print usedURLS
    while url in usedURLS:
         url = zoneNames[zone] + str(counter) + '.' + username + '.vpn.windmaker.net'
         counter += 1
    
    print url
    print region
    cursor = db.cursor()
    update_query = ("UPDATE servers SET name='{}' , true_zone='{}' , provider='{}' , status='Setting up...'  WHERE token='{}';".format(url, region, provider, token))
    cursor.execute(update_query)
    db.commit()
    cursor.close()
    if provider == 'DigitalOcean':
        ip , dropletID = createDropletDigitalOcean(url, region)
        print ip

    cursor = db.cursor()
    update_query = ("UPDATE servers SET machine_id={} WHERE token='{}';".format(dropletID, token))
    cursor.execute(update_query)
    db.commit()
    cursor.close()

    response = os.system("ping -c 1 " + ip)
    while response != 0:
        sleep(0.5)
        response = os.system("ping -c 1 " + ip)
    sleep(10)
    print "Set up config"
    setUpVPNServer(userId,token,url,dropletID,ip)
    cursor = db.cursor()
    update_query = ("UPDATE servers SET status='Running'  WHERE token='{}';".format(token))
    cursor.execute(update_query)
    db.commit()
    cursor.close()

def poweroff(token):
    cursor = db.cursor()
    query = ("SELECT machine_id , provider FROM servers WHERE token='{}';".format(token))
    cursor.execute(query)
    results = cursor.fetchall()[0]
    cursor = db.cursor()
    print results
    if results[1] == 'DigitalOcean':
         manager = digitalocean.Manager(token=APIToken)
         my_droplets = manager.get_all_droplets()
         for droplet in my_droplets:
              if str(droplet).split(' ')[0] == str(results[0]):
                   print "Lo apago"
                   droplet.shutdown()
              #print droplet
              #print str(droplet).split(' ') 
    #droplet.shutdown()

class theThread(threading.Thread):
    def __init__(self, action, zone=None, userId=None, token=None):
         threading.Thread.__init__(self)
         self.action = action
         self.zone = zone
         self.userId = userId
         self.zone = zone
         self.token = token

    def run(self):
         if self.action == 'create':
              createDroplet(self.zone, self.userId, self.token)
         elif self.action == 'poweroff':
              poweroff(self.token)



class GetHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_path = urlparse.urlparse(self.path)
        message_parts = []
        if parsed_path.path == '/createserver' or parsed_path.path == '/poweroff':
            arguments = dict()
            print(self.client_address)
            args = parsed_path.query.split('&')
            for arg in args:
                splited = arg.split('=')
                arguments[splited[0]] = splited[1]
            print(arguments)
            if 'token' in arguments:
                print "Token ->" + arguments['token']
                userId, zone = getInfoFromToken(arguments['token'])
                if userId != None:
                    print "Machine id - {}".format(userId)
                    print "Zone - {}".format(zone)
		    if parsed_path.path == '/createserver':
		        t = theThread('create', int(zone), userId, arguments['token'])  
                    elif parsed_path.path == '/poweroff':
                        t = theThread('poweroff', int(zone), userId, arguments['token'])
                    t.start()  
                    #createDroplet(int(zone), userId, arguments['token'])
        for name, value in sorted(self.headers.items()):
            message_parts.append('%s=%s' % (name, value.rstrip()))
        message_parts.append('')
        message = '\r\n'.join(message_parts)
        self.send_response(200)
        self.end_headers()
        self.wfile.write("Ok")
        return


if __name__ == '__main__':
    from BaseHTTPServer import HTTPServer

    server = HTTPServer(('0.0.0.0', 8888), GetHandler)
    print 'Starting server, use <Ctrl-C> to stop'
    server.serve_forever()
