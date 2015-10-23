from time import sleep
import os
import digitalocean

APIToken = '82bede0e660f5872d5988a4785fa6a10aa8f55cb7e52882906ca89c1b6a2c773'
dropletName = 'test'
dropletRegion = 'lon1'
sshKeyList = ["ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQD04ZoHu9qszy61gVeggjYiR/KLdZrFOpT6qiULOj1xc4ZX6TuHLFE1WklzYjRhqukVNPRlsg3lxG8yBOxSQmAmKYQgJr2lA0JqORpRWWodDqKp7a0WKuaur6UJeTSqUUrOJq/hktUcTLlD3x5miumx1g8+QjkSi4zVe4UXenv8fnddcZJD8LxU6aNJzDmlEDw/3YjADdUhxTS6n95WfoRPD9oS96BlEIBNhsSZExtchs84CNR/g8Rp+QxchySQ/nqaJO6yHBKK/ZUFySQYwg+UfRPxWK9z8JV+VFrWVKZSJ7qiuWCnr9R4IMMLhKhpwFUuqqO57AZghQY4JyQ5XUxh root@Paula"]

manager = digitalocean.Manager(token=APIToken)

droplet = digitalocean.Droplet(token=APIToken,
name=dropletName,
region='lon1', # New York 2
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

response = os.system( "ping -c 1 " + str(ip) )
while response != 0:
	sleep(0.5)
	response = os.system( "ping -c 1 " + str(ip) )


print "LISTO"
