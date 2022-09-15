
# 实现两个数值的编码,可以指定value数位的大小以及间隔大小
# a与b是两个value值，n是value的位数，block为间隔大小
def testEncoding(a, b, n, block):
    value_max = pow(2, n) - 1
    print("保证每个value <=", value_max)
    if (a > value_max) | (b > value_max):
        print("数值超出设定范围,无法编码")
        return 0
    m = "0" * block + bin(a)[2:].zfill(n) + "0" * block + bin(b)[2:].zfill(n)
    print("0" * block + "+" + bin(a)[2:].zfill(n) + "+" + "0" * block + "+" + bin(b)[2:].zfill(n))
    print("合并结果为" + m)
    # 转换成十进制
    m = int(m, 2)
    return m


# 对完成同态计算后的值进行解码，输出为其结果数组
# w为一个十进制数,length为规定的二进制数的bit位数,n为value的位数，block间隔大小
def testDecoding(w, length, n, block):
    # 规范二进制数
    w = bin(w)[2:].zfill(length)
    print(w)
    # 含有的value的个数
    num = int(length / (block + n))
    # 获得二进制的结果数组
    value_sum_list = [w[block * i + n * i - n - 1:i * (block + n)] for i in range(0, num + 1)]
    # 转换为十进制的结果数组
    value_sum_list_10 = [int(value_sum_list[i], 2) for i in range(1, num + 1)]
    for value in value_sum_list_10:
        print(value)
    return value_sum_list_10
