from data_parser import DataParser
from trend_analyser import TrendAnalyser
from matplotlib import pyplot

data_parser = DataParser()
trend_analyser = TrendAnalyser()

data = data_parser.load_data('./data/table_dell.csv')

print ("Data length: ", len(data))
chunked_data = data_parser.partition_into_chunks(data)
print ("Chunked data length: ", len(chunked_data))




pyplot.plot(data)