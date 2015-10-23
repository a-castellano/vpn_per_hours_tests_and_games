import digitalocean

APIToken = '82bede0e660f5872d5988a4785fa6a10aa8f55cb7e52882906ca89c1b6a2c773'

manager = digitalocean.Manager(token=APIToken)
my_droplets = manager.get_all_droplets()
for droplet in my_droplets:
    print droplet.id
    
