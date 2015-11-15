from time import sleep
import os
import subprocess
import digitalocean
import route53

conn = route53.connect(
    aws_access_key_id='AKIAIRXB2NBW6JBJSMRQ',
    aws_secret_access_key='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',
)

APIToken = '82bede0e660f5872d5988a4785fa6a10aa8f55cb7e52882906ca89c1b6a2c773'
dropletName = 'test'
dropletRegion = 'lon1'
sshKeyList = ["ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQD04ZoHu9qszy61gVeggjYiR/KLdZrFOpT6qiULOj1xc4ZX6TuHLFE1WklzYjRhqukVNPRlsg3lxG8yBOxSQmAmKYQgJr2lA0JqORpRWWodDqKp7a0WKuaur6UJeTSqUUrOJq/hktUcTLlD3x5miumx1g8+QjkSi4zVe4UXenv8fnddcZJD8LxU6aNJzDmlEDw/3YjADdUhxTS6n95WfoRPD9oS96BlEIBNhsSZExtchs84CNR/g8Rp+QxchySQ/nqaJO6yHBKK/ZUFySQYwg+UfRPxWK9z8JV+VFrWVKZSJ7qiuWCnr9R4IMMLhKhpwFUuqqO57AZghQY4JyQ5XUxh root@Paula"]

manager = digitalocean.Manager(token=APIToken)

droplet = digitalocean.Droplet(token=APIToken,
name=dropletName,
region='ams2', # New York 2
image='ubuntu-14-04-x64', # Ubuntu 14.04 x64
ssh_keys = sshKeyList,
size_slug='512mb', # 512MB
backups=False)

droplet.create()
dropletID = droplet
print dropletID

sleep(30)

dropletData = manager.get_droplet(dropletID)
ip = dropletData.ip_address
print ip

print "Apuntamos la maquina"
conn = route53.connect(
    aws_access_key_id='AKIAIRXB2NBW6JBJSMRQ',
    aws_secret_access_key='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',
)

zone = conn.get_hosted_zone_by_id('ZPEB3E12BAWA8')
name_to_match = 'testuk.vpn.windmaker.net.'

encontrado = False
for record_set in zone.record_sets:
        print(record_set.name)
        if record_set.name == name_to_match:
                print("es este")
                break;

if not encontrado:
        print "Lo creamos"
        new_record, change_info = zone.create_a_record(name='testuk.vpn.windmaker.net.',values=[str(ip)],)


response = os.system( "ping -c 1 " + str(ip) )
while response != 0:
	sleep(0.5)
	response = os.system( "ping -c 1 " + str(ip) )


print "Lanzamos script de instalacion (ansible)"
inventory = open('inventories/inventory.ini','w')
inventory.write('[target]\n')
inventory.write(ip + '\n')
inventory.close()
subprocess.check_call('/usr/bin/ansible-playbook ../ansible/pptp_setup.yml -i inventories/inventory.ini', shell=True)

