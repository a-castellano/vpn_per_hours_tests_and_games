from BaseHTTPServer import BaseHTTPRequestHandler
import urlparse

class GetHandler(BaseHTTPRequestHandler):
    
    def do_GET(self):
        parsed_path = urlparse.urlparse(self.path)
#        message_parts = [
#                'CLIENT VALUES:',
#                'client_address=%s (%s)' % (self.client_address,
#                                            self.address_string()),
#                'command=%s' % self.command,
#                'path=%s' % self.path,
#                'real path=%s' % parsed_path.path,
#                'query=%s' % parsed_path.query,
#                'request_version=%s' % self.request_version,
#                '',
#                'SERVER VALUES:',
#                'server_version=%s' % self.server_version,
#                'sys_version=%s' % self.sys_version,
#                'protocol_version=%s' % self.protocol_version,
#                '',
#                'HEADERS RECEIVED:',
#                ]
	message_parts = []
	if parsed_path.path == '/createserver':
		print(self.client_address)
		arguments = parsed_path.query.split('&')
		print(arguments)
		#print(parsed_path.query)
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
    server = HTTPServer(('192.168.56.101', 8888), GetHandler)
    print 'Starting server, use <Ctrl-C> to stop'
    server.serve_forever()
