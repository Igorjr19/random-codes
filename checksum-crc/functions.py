import socket

def str_to_bin(message: str) -> bytes:
    return ''.join(format(ord(char), '08b') for char in message)

def bin_to_str(sequence: bytes) -> str:
    return ''.join(chr(int(sequence[i:i+8], 2)) for i in range(0, len(sequence), 8))

def gen_checksum(sequence: bytes) -> bytes:
    n = 8
    k = len(sequence) // n
    segments = []
    for i in range(0, k * n, n):
        segments.append(sequence[i:i+n])
    for i in range(len(segments)):
        segments[i] = int(segments[i], 2)
    checksum = sum(segments)
    checksum = bin(checksum)[2:]
    checksum = ''.join(['0' if bit == '1' else '1' for bit in checksum])
    return sequence + checksum, k, n

def check_checksum(sequence: bytes, k: int, n: int) -> (bool, bytes):
    segments = []
    for i in range(0, k  * n, n):
        segments.append(sequence[i:i+n])
    segments.append(sequence[k*n:])
    for i in range(len(segments)):
        segments[i] = int(segments[i], 2)
    checksum = sum(segments)
    checksum = bin(checksum)[2:]
    checksum = ''.join(['0' if bit == '1' else '1' for bit in checksum])
    if not checksum.__contains__('1'):
        return True, sequence[:k * n]
    else:
        return False, bytes('invalid sequence', 'utf-8')

def gen_crc(sequence: bytes, G: bytes) -> bytes:
    msg = sequence
    sequence += '0' * (len(G) - 1)
    sequence = [int(bit) for bit in sequence]
    G = [int(bit) for bit in G]
    for i in range(len(sequence) - len(G) + 1):
        if sequence[i] == 1:
            for j in range(len(G)):
                sequence[i+j] ^= G[j]
    return msg + ''.join(str(bit) for bit in sequence)[-len(G) + 1:]

def check_crc(sequence: bytes, G: bytes) -> bytes:
    msg = sequence
    sequence += '0' * (len(G) - 1)
    sequence = [int(bit) for bit in sequence]
    G = [int(bit) for bit in G]
    for i in range(len(sequence) - len(G) + 1):
        if sequence[i] == 1:
            for j in range(len(G)):
                sequence[i+j] ^= G[j]
    if sequence[-len(G) + 1:].__contains__('1'):
        return False, bytes('invalid sequence', 'utf-8')
    else:
        return True, msg[:len(msg) - len(G) + 1]

def enviar(message: str):
    host = socket.gethostname()
    port = 5000
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        message = bytes(message, 'UTF-8')
        s.connect((host, port))
        s.send(message)
        s.close()

def receber():
    host = socket.gethostname()
    port = 5000

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen(1)
        conn, addr = s.accept()
        data = conn.recv(1024)
        data = data.decode('utf-8')
        conn.close()
        s.close()
        return data
