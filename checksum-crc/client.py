import functions as f

G = '1101'

print('Enviando Mensagens:\n')

i = 0
while True:
    if i == 0:
        msg = input('Digite a mensagem (Checksum): ')
        if msg == '':
            continue
        msg = f.str_to_bin(msg)
        msg, k, n = f.gen_checksum(msg)
        f.enviar(f.str_to_bin(str(k)))
        f.enviar(f.str_to_bin(str(n)))
        f.enviar(msg)
        i = 1
    else:
        msg = input('Digite a mensagem (CRC): ')
        if msg == '':
            continue
        msg = f.str_to_bin(msg)
        msg = f.gen_crc(msg, G)
        f.enviar(msg)
        i = 0
