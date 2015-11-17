from BaseHTTPServer import BaseHTTPRequestHandler
import urlparse
import MySQLdb
from time import sleep
import os
import subprocess
import digitalocean
import route53
import random

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
    5: {'DigitalOcean': ['tor11']}
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


def setUpVPNServer(userId,token,url,dropletID):
    cursor = db.cursor()
    query = ("SELECT name, password FROM vpnusers WHERE user_id={};".format(userId))
    cursor.execute(query)
    users = cursor.fetchall()
    print users

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
    print "Set up config"
    setUpVPNServer(userId,token,url,dropletID)


class GetHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_path = urlparse.urlparse(self.path)
        message_parts = []
        if parsed_path.path == '/createserver':
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
                    createDroplet(int(zone), userId, arguments['token'])
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

    server = HTTPServer(('192.168.155.1', 8888), GetHandler)
    print 'Starting server, use <Ctrl-C> to stop'
    server.serve_forever()
