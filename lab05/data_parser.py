import math
import csv


class DataParser():

    def __init__(self):
        pass

    def label_data(self, raw_data):
        labeled_data = {}

        labeled_data["DATE"] = raw_data[0]
        labeled_data["TIME"] = raw_data[1]
        labeled_data["OPEN"] = raw_data[2]
        labeled_data["HIGH"] = raw_data[3]
        labeled_data["LOW"] = raw_data[4]
        labeled_data["CLOSE"] = raw_data[5]
        labeled_data["EARNINGS"] = raw_data[6]

        return labeled_data

    def load_data(self, path):
        data = []

        with open(path, 'r') as csv_file:
            csv_data = csv.reader(csv_file, delimiter=',')
            for row in csv_data:
                labeled_data = self.label_data(row)
                data.append(labeled_data)

        return data

    def partition_into_chunks(self, all_data, chunk_size=5):

        number_of_chunks = math.ceil(float(len(all_data)) / float(chunk_size))
        chunked_data = []

        for chunk_num in range(int(number_of_chunks)):
            chunk = all_data[chunk_num*chunk_size:chunk_num*chunk_size+chunk_size]
            chunked_data.append(chunk)

        return chunked_data

    def get_parameter_values_as_list(self, data, parameter_name):
        values = []
        for entry in data:
            for key, value in entry.iteritems():
                if key == parameter_name:
