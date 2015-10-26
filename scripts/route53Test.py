import route53

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
	new_record, change_info = zone.create_a_record(name='testuk.vpn.windmaker.net.',values=['46.101.24.102'],)
