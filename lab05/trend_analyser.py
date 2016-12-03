import numpy as np
from scipy import stats

class TrendAnalyser():

    def __init__(self):
        pass

    def moving_average(self, interval, window_size=5):
        window = np.ones(int(window_size)) / float(window_size)
        return np.convolve(interval, window, 'same')

    def calculate_linear_regression_slope(self, X, Y):
        slope, intercept, r_value, p_value, std_err = stats.linregress(X, Y)
        return slope

    def get_data_trend(self, data):
        lin_reg_slope = self.calculate_linear_regression_slope(data["x"], data["y"])
        moving_average_1 = self.moving_average(data["y"])

        return moving_average_1[0] < moving_average_1[-1], lin_reg_slope >= 0