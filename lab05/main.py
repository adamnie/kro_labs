import csv
import math
import numpy as np
from scipy import stats


def label_data(raw_data):
    labeled_data = {}

    labeled_data["DATE"] = raw_data[0]
    labeled_data["TIME"] = raw_data[1]
    labeled_data["OPEN"] = raw_data[2]
    labeled_data["HIGH"] = raw_data[3]
    labeled_data["LOW"] = raw_data[4]
    labeled_data["CLOSE"] = raw_data[5]
    labeled_data["EARNINGS"] = raw_data[6]

    return labeled_data

def load_data(path):
    data = []

    with open(path, 'r') as csv_file:
        csv_data = csv.reader(csv_file, delimiter=',')
        for row in csv_data:
            labeled_data = label_data(row)
            data.append(labeled_data)

    return data

def  partition_into_chunks(all_data, chunk_size=5):

    number_of_chunks = math.ceil(float(len(all_data)) / float(chunk_size))
    chunked_data = []

    for chunk_num in range(int(number_of_chunks)):
        chunk = all_data[chunk_num*chunk_size:chunk_num*chunk_size+chunk_size]
        chunked_data.append(chunk)

    return chunked_data

def moving_average(data, chunk_size=5) :
    ret = np.cumsum(a, dtype=float)
    ret[n:] = ret[n:] - ret[:-n]
    return ret[n - 1:] / n

def calculate_linear_regression_slope (X,Y):
    slope, intercept, r_value, p_value, std_err = stats.linregress(X, Y)
    print(slope)
    return slope

def get_data_trend(data):
    last_entry = data[-1]
    lin_reg_slope = calculate_linear_regression_slope(data)
    moving_average = moving_average(data)
    return (moving_average[-1] > moving_average[-2], lin_reg_slope >= 0)


data = load_data('./data/table_dell.csv')

print ("Data length: ", len(data))
chunked_data = partition_into_chunks(data)
print ("Chunked data length: ", len(chunked_data))


print(get_data_trend([1, 2, 3, 4]))
