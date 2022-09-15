import Coding
from phe import paillier

# 设定value的位数n，设定值与值之间的间隔数，
n = 9
block = 5

val1 = [1, 8, 10, 5]
val2 = [25, 6, 9, 8]


public_key, private_key = paillier.generate_paillier_keypair()

# 添加测试数据

m1 = Coding.testEncoding(val1, n, block)
m2 = Coding.testEncoding(val2, n, block)

message_list = [m1, m2]
# 加密操作
encrypted_message_list = [public_key.encrypt(m) for m in message_list]

# 同态运算
x, y = encrypted_message_list
z = x + y

# 解密操作
q = private_key.decrypt(z)
Coding.testDecoding(q,  n, block, len(val1))

