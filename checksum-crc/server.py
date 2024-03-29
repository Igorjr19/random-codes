import functions as f

G = '1101'

print('Recebendo Mensagens:\n')

i = 0
while True:
    if i == 0:
        k = int(f.bin_to_str(f.receber()))
        n = int(f.bin_to_str(f.receber()))
        msg = f.receber()
        msg = f.check_checksum(msg, k, n)
        if msg[0] == 0:
            print('Checksum inválido')
            i = 1
            continue
        msg = f.bin_to_str(msg[1])
        print('Recebido (Checksum): ' + msg)
        i = 1
    else:
        msg = f.receber()
        msg = f.check_crc(msg, G)
        if msg[0] == 0:
            print('CRC inválido')
            i = 0
            continue
        msg = f.bin_to_str(msg[1])
        print('Recebido (CRC): ' + msg)
        i = 0
