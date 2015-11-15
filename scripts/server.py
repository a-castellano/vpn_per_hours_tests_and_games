from BaseHTTPServer import BaseHTTPRequestHandler
import urlparse
import MySQLdb

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
                print arg
                splited = arg.split('=')
                print splited
                arguments[splited[0]] = splited[1]
            print(arguments)
            if 'token' in arguments:
                print "Token " + arguments['token']

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
