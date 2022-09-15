import Coding
from phe import paillier  # 开源库

n = 5
block = 5

a = 10
b = 30
c = 20
d = 20


public_key, private_key = paillier.generate_paillier_keypair()

# 添加测试数据

m1 = Coding.testEncoding(a, b, n, block)
m2 = Coding.testEncoding(c, d, n, block)

message_list = [m1, m2]
# 加密操作
encrypted_message_list = [public_key.encrypt(m) for m in message_list]

# 同态运算
x, y = encrypted_message_list
z = x + y

# 解密操作
print(private_key.decrypt(x))
print(private_key.decrypt(y))
print(private_key.decrypt(z))
q = private_key.decrypt(z)
Coding.testDecoding(q, 20, n, block)

print("验证："+"a=",a," c=",c,"   a+c=",a+c)
print("验证："+"b=",b," d=",d,"   b+d=",b+d)








