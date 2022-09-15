
# value为插入值数组，n是value的位数，block为间隔大小
# 插值编码函数
def testEncoding(value, n, block):
    value_max = pow(2, n) - 1
    # print("保证每个value <=", value_max)
    m = ""
    num = len(value)
    for i in range(0, num):
        if value[i] > value_max:
            print("数值超出设定范围,无法编码")
            return 0
        m = m + "0" * block + bin(value[i])[2:].zfill(n)
    # print("合并结果为" + m)
    # 转换成十进制
    m = int(m, 2)
    return m


# 对完成同态计算后的值进行解码，输出为其结果数组
# w为一个十进制数,n为value的位数，block间隔大小,num为值个数
def testDecoding(w, n, block, num):
    # 规范二进制数,length为规定的二进制数的bit位数
    length = (n + block) * num
    w = bin(w)[2:].zfill(length)
    # print(w)
    # 含有的value的个数
    num = int(length / (block + n))
    # 获得二进制的结果数组
    value_sum_list = [w[block * i + n * i - n - 1:i * (block + n)] for i in range(0, num + 1)]
    # 转换为十进制的结果数组
    value_sum_list_10 = [int(value_sum_list[i], 2) for i in range(1, num + 1)]
    for value in value_sum_list_10:
        print(value)
    return value_sum_list_10

