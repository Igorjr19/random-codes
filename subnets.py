import ipaddress
import numpy as np

def ip_to_bin(ip: ipaddress.IPv6Network):
  return '{:#b}'.format(ip.network_address)

def bin_to_ip(bin_ip: str):
  ip = ipaddress.IPv6Address(int(bin_ip, 2))
  return ip

def rightmost(ip: ipaddress.IPv6Address, mask: int, num_subnets: int):
  if(num_subnets > 2 ** (128 - mask)):
    raise Exception('Número de subnets superior ao número de subnets que pode ser gerado')

  bin_ip = ip_to_bin(ip)
  num = int(2 ** np.ceil(np.log2(num_subnets)))
  new_mask = mask + num.bit_length() - 1

  subnets = []
  for i in range(num):
    net = bin_ip[2:][:mask]
    host = bin(i)[2:].zfill(num.bit_length() - 1)
    host = host + '0'.zfill(128 - mask - (num.bit_length() - 1))
    address = bin_to_ip(net + host)
    subnets.append(ipaddress.IPv6Address(address))

  return subnets, new_mask

def leftmost(ip: ipaddress.IPv6Address, mask: int, num_subnets: int):
  if(num_subnets > 2 ** (128 - mask)):
    raise Exception('Número de subnets superior ao número de subnets que pode ser gerado')

  bin_ip = ip_to_bin(ip)
  num = int(2 ** np.ceil(np.log2(num_subnets)))
  new_mask = mask + num.bit_length() - 1

  subnets = []
  for i in range(num):
    net = bin_ip[2:][:mask]
    host = bin(i)[2:].zfill(num.bit_length() - 1)
    host = host[::-1]
    host = host + '0'.zfill(128 - mask - (num.bit_length() - 1))
    address = bin_to_ip(net + host)
    subnets.append(ipaddress.IPv6Address(address))

  return subnets, new_mask

ip = ipaddress.IPv6Network('2001:db8::/32')

r = rightmost(ip, 32, 5)
l = leftmost(ip, 32, 5)

print(f'Subnets geradas para o ip {ip} usando rightmost:')
print(r)
print(f'\nSubnets geradas para o ip {ip} usando leftmost:')
print(l)
