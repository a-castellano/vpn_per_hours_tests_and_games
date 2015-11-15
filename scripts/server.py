from BaseHTTPServer import BaseHTTPRequestHandler
import urlparse
import MySQLdb
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

zones = {
	1 : 'nyc1'
}


db_host = 'kafir.es'
user = 'vpn'
password = '=W5Z+^_+6~Cc2*6s4%7_2=^8~q^c|=|=!u84~.%PK'
database = 'vpn'
db = MySQLdb.connect(host=db_host, user=user, passwd=password, db=database)


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
		cursor=db.cursor()
		query = ("SELECT user_id, zone FROM servers WHERE token='{}';".format(arguments['token']))
		cursor.execute(query)
		serverToCreate = cursor.fetchone() 
		cursor.close()
		print serverToCreate
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
