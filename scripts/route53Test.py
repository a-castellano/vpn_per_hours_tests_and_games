import route53

conn = route53.connect(
    aws_access_key_id='AKIAIRXB2NBW6JBJSMRQ',
    aws_secret_access_key='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',
)


for zone in conn.list_hosted_zones():
	print(zone.name)
