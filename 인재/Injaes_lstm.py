import tensorflow as tf
import os
import pandas as pd
import math
import numpy as np
import matplotlib.pyplot as plt
import csv


PH = 5

def readData(filename):
    #실제 반환될 배열
    EntryData = []
    x_data = []
    y_data = []
    A1c_data = []
    glucose_data =[]
    ####임시 배열
    tmp_x = []
    tmp_y = []
    tmp_A1c = []
    tmp_glucose = []
    with open(filename,'r') as f:
        # 읽기모드로 파일을 연다.
        for line in f:
            EntryData.append(float(line.split(',')[0]))
            # EntryData에 float형으로 파일의 각 라인의 ','앞의 값들을 추가한다.

    df = pd.Series(EntryData)
    # Series를 사용하여 EntryData에 인덱스를 추가한다
        # 예)  0   4
        #      1   7
        #      2  -5
        #      3   3

    A1c = df[0:1]
    # 0부터 1-1의 데이터 즉, df[0]의 값을 A1c에 저장한다.
    # A1c 는 당화혈색소이다.

    # 당화혈색소란,  혈색소는 적혈구 내부에서 관찰되는 산소운반 단백질입니다.
    #                포도당이 혈중을 순환하면 이 중 일부는 자연적으로 A형 혈색소에 결합합니다.
    #                포도당과 혈색소가 결합한 분자를 당화되었다고 합니다.
    #                혈중 포도당 농도가 높을수록 더 많은 당화 혈색소가 생성됩니다.
    #                일단 포도당이 혈색소에 결합하면 정상적으로 120일인 적혈구의 수명을 다할 때까지 결합된 상태를 유지합니다.
    #                포도당과 A형 혈색소가 결합한 조합을 HbA1c 혹은 A1c라고 합니다.

    glucose = df[1:2]
    # 1부터 2-1의 데이터 즉, df[1]의 값을 glucose에 저장한다.    glucose : 포도당
    while True:

        for i in df[1:8]:
            tmp_x.append([float(i)])
            # df[1]~df[7]의 값을 차례대로 float화하여 tmp_x에 추가한다.
        tmp_y.append(float(df[7 + (PH/5)]))
        # df[8]의 값을 tmp_y에 저장한다.
        tmp_A1c.append(float(A1c))
        # A1c의 값을 float화하여 tmp_A1c에 저장한다.
        tmp_glucose.append(float(glucose))
        # glucose의 값을 float화하여 tmp_glucose에 저장한다.

        x_data.append(tmp_x)
        # x_data는 한 행당 7개의 데이터가 들어있다.
        y_data.append(tmp_y)
        A1c_data.append(tmp_A1c)
        glucose_data.append(tmp_glucose)
        # 각각 tmp_...에 저장된 값들을 실제 반환될 배열들에 추가한다.

        tmp_x = []
        tmp_y = []
        tmp_A1c = []
        tmp_glucose = []
        # tmp_... 변수들을 초기화한다.

        df = df.shift(-1)
        # df의 데이터를 한칸씩 위로 밀고 맨 마지막의 데이터를 nan으로 설정
        if(math.isnan(df[7+(PH/5)])):
            break
            # df[8] = nan 이면 while문을 벗어난다.

        #for i in range(1,9):
        #    print(df[i])

    if(len(x_data[-1]) != 7):
       xSize = 7-len(x_data[-1])
        # x_data의 마지막 데이터 행의 데이터수가 7개보다 부족하면 xSize를 부족한수로 지정
       for i in range(xSize):
           x_data[-1].append(0.0)
            #x_data 마지막행의 빈 공간 데이터를 빈만큼 0.0으로 채운다

    if(len(y_data[-1])!=1):
       y_data[-1].append(0.0)
        # y_data의 마지막 데이터값이 nan이면 0.0으로 바꿔준다.

    x_data = np.asarray(x_data)
    # asarray를 사용하여 x_data를 배열형태로 만든다    ?행7열
    y_data = np.asarray(y_data)
    # asarray를 사용하여 y_data를 배열형태로 만든다     ?행 1열
    A1c_data = np.asarray(A1c_data)
    # asarray를 사용하여 A1c_data를 배열형태로 만든다   ?행 1열
    glucose_data = np.asarray(glucose_data)
    # asarray를 사용하여 glucose_data를 배열형태로 만든다   ?행 1열
    data = [x_data,y_data,A1c_data,glucose_data]        #    7 , 1 , 1  , 1
    return data

    # readData 함수의 리턴값은 배열형태의 값들을 모아둔 data



filename = os.listdir("sch")
# sch 폴더의 하위에 있는 파일들을 불러와 filename에 리스트로 저장
print(filename[5])
# 1185429_test.csv 이 출력됨  -> filename에 파일목록들이 잘 들어갔는지 확인하기위한 출력문
train_data_name = []
test_data_name = []

for fn in filename:
    if fn.find("test") != -1:
        test_data_name.append(fn)
        # test 데이터들을 test_data_name에 리스트로 저장
    elif fn.find("train") != -1:
        train_data_name.append(fn)
        # train 데이터들을 train_data_name에 리스트로 저장

glucoseList = []
glucose_train = []
glucose_test = []

A1cList = []
A1c_train = []
A1c_test = []

total_x_data = []
total_y_data = []

train_x_data = []
train_y_data = []

for fn in train_data_name:
    if fn.find("885633") != -1:
        print(fn+"제외")
        # 이름에 885633 인 파일을 제외시킨다
    elif fn.find("365303") != -1:
        print(fn+"제외")
        # 이름에 365303 인 파일을 제외시킨다
    else:
        x,y,a,g = readData("sch/"+str(fn))
        # x,y,a,g 에 readData의 리턴값인 [x_data, y_data, A1c_data, glucose_data]를 각 변수에 저장한다.

        train_x_data.append(x)
        total_x_data.append(x)

        train_y_data.append(y)
        total_y_data.append(y)

        A1cList.append(a)
        A1c_train.append(a)

        glucoseList.append(g)
        glucose_train.append(g)





test_x_data = []
test_y_data = []
for fn in test_data_name:
    if fn.find("885633") != -1:
        print(fn+"제외")
        # 이름에 885633 인 파일을 제외시킨다.
    elif fn.find("365303") != -1:
        print(fn+"제외")
        # 이름에 365303 인 파일을 제외시킨다.
    else:
        x,y,a,g = readData("sch/"+str(fn))
        # x,y,a,g 에 readData의 리턴값인 [x_data, y_data, A1c_data, glucose_data]를 각 변수에 저장한다.

        test_x_data.append(x)
        total_x_data.append(x)

        test_y_data.append(y)
        total_y_data.append(y)

        A1cList.append(a)
        A1c_test.append(a)

        glucoseList.append(g)
        glucose_test.append(g)

#print(glucoseList[0])
print(test_x_data[5])


X = tf.placeholder(tf.float32,shape=[None,7,1])
Y = tf.placeholder(tf.float32,shape=[None,1])
A1c = tf.placeholder(tf.float32,shape=[None,1])
G = tf.placeholder(tf.float32,shape=[None,1])
# placeholer를 사용해 각 행과열의 텐서들을 생성합니다.

'''
W = tf.Variable(tf.random_uniform([1,15], minval = -1, maxval = 1, dtype = tf.float32))
b = tf.Variable(tf.zeros([1,15],dtype = tf.float32))

W1 = tf.Variable(tf.random_uniform([15,1], minval = -1, maxval = 1, dtype = tf.float32))
b1 = tf.Variable(tf.zeros([1,1],dtype = tf.float32))'''

cell = tf.contrib.rnn.BasicLSTMCell(num_units=15,state_is_tuple=True,activation=tf.tanh)
# num_unit = hidden_size 즉, 출력의 크기가 15,    2-튜플형태로
outputs, _states = tf.nn.dynamic_rnn(cell,X,dtype=tf.float32)
Y_p = tf.contrib.layers.fully_connected(outputs[:,-1],1,activation_fn=None)
#  셀에서 나온 혈당 데이터
Y_A = tf.contrib.layers.fully_connected(A1c,1,activation_fn=tf.sigmoid)
#  a1c 가중치 데이터
Y_g = tf.contrib.layers.fully_connected(G,1,activation_fn=tf.sigmoid)
#  은닉층에 추가한 글루코오스 파라미터
Y_pr = tf.contrib.layers.fully_connected(Y_p+Y_A+Y_g,15,activation_fn=None)
#  셀에서 나온 혈당데이터와 a1c 가중치 데이터를 함친것
Y_pre =  tf.contrib.layers.fully_connected(Y_pr,1,activation_fn=None)
# Y_pre 의 15개 값을 하나로 합친 값

rmse = tf.sqrt(tf.reduce_mean(tf.square(tf.subtract(Y, Y_pre))))
#    R M S E    평균 제곱근 오차
#    tf.subtract = 뺄셈  ,  tf.square = 제곱 ,  tf.reduce_mean = 평균  ,   tf.reduce_mean = 평균   ,    tf.sqrt = 제곱근
#    (실제값 - 예측값)제곱의 평균을 제곱근한것이 평균 제곱근 오차 즉, RMSE(Root Mean Sqaure Arror) 이다.

loss = tf.reduce_sum(tf.square(Y_pre - Y))
#loss =  (예측값 - 실제값)들의 각 제곱의 합
optimizer = tf.train.AdamOptimizer(learning_rate = 0.01)
# learning_rate를 0.01로 하는 Adam 경사하강법을 시행합니다.
# 최솟값을 찾기위해 사용한다.
train = optimizer.minimize(loss)
# loss의 최솟값을 train에 저장시킨다.



sess = tf.Session()
sess.run(tf.global_variables_initializer())

for loop in range(len(total_x_data)):
    for i in  range(700):
        sess.run(train,feed_dict = {X:total_x_data[loop],Y:total_y_data[loop],A1c:A1cList[loop],G:glucoseList[loop]})
        #sess.run(train,feed_dict = {X:total_x_data[loop],Y:total_y_data[loop]})
    print(str(loop / len(total_x_data) * 100) + "%")


pre_List = []
for loop in range(len(test_x_data)):
    for i,k in enumerate(test_x_data[8]):
        ln = sess.run(Y_pre,feed_dict={X:[k],A1c:A1c_test[8],G:glucose_test[8]})
        print("실제혈당 : "+str(test_y_data[8][i])+"예측혈당 : "+str(ln[0][0]))
        pre_List.append(ln[0][0])
        #print([sess.run(Y_p,feed_dict={X:[k]})[0][0],10.0])
    break;


rmse_total = 0.0
rmse_one = 0.0
total_num = 0
one_person_num = 0
for size in range(len(test_x_data)):
    one_person_num = 0
    rmse_one = 0
    for i,k in enumerate(test_x_data[size]):
        total_num += 1
        one_person_num += 1
        #print(sess.run(rmse,feed_dict={X:[k],Y:[test_y_data[size][i]],A1c:[A1c_test[size][i]],G:[glucose_test[size][i]]}))
        tmp = sess.run(rmse,feed_dict={X:[k],Y:[test_y_data[size][i]],A1c:[A1c_test[size][i]],G:[glucose_test[size][i]]})
        rmse_total += tmp
        rmse_one += tmp
    print(str(size+1)+"번째 환자 rmse : "+str(rmse_one/float(one_person_num)))

rmse_total = rmse_total / float(total_num)
print("전체 평균 rmse : "+str(rmse_total))



plt.plot(pre_List,color="red")      # 예측혈당
plt.plot(test_y_data[8],color="blue")      # 실제혈당
plt.show()
