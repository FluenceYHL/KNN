#include "scopeguard.h"
#include "gnuplot.hpp"
#include "assert.h"

namespace {
	int hash(int *arr, const int l, const int r) {
		int res = 0;
		// std::cout << "l = " << l << "\tr = " << r << "\n";
		for(int i = l; i < r; ++i) {
			res = (res << 1) + arr[i];
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
		std::cout << "res  :  " << res << "\n";
		return res;
	}

	std::string hash(int arr[][14], const int len) {
		std::cout << "哈希的矩阵是  :  \n";
		// for(int l = 0;l < 14; ++l) {
		// 	for(int r = 0;r < 14; ++r)
		// 		std::cout << arr[l][r] << " ";
		// 	std::cout << "\n";
		// }

		std::string res = "";
		for(int i = 0;i < len; ++i) {
			// for(int j = 0;j < len; ++j)
			// 	std::cout << arr[i][j] << " ";
			// std::cout << "\n";
			res += std::to_string(hash(arr[i], 0, len >> 1));
			res += std::to_string(hash(arr[i], len >> 1, len));
			// std::cout << "res  :  " << res << "\n";
		}
		return res;
	}
}

namespace YHL {

	class KNN {
	private:
		std::vector<int> answers;
		std::vector< std::vector<int> > dataSet;
	public:
		void train() {
			std::cout << "开始读文件\n";
			std::ifstream in("./Minist_Rand.txt");
			ON_SCOPE_EXIT([&]{
				in.close();
			});
			assert(in);
			for(int i = 0;i < 60000; ++i) {
				int matrix[28][28];
				for(int l = 0;l < 28; ++l)
					for(int r = 0;r < 28; ++r)
						in >> matrix[l][r];
				int handled[14][14];
				for(int l = 0;l < 14; ++l) {
					for(int r = 0;r < 14; ++r) {
						int cnt = 0;
						int x = l << 1;
						int y = r << 1;
						if(matrix[x][y] == 1) ++cnt;
						if(matrix[x + 1][y] == 1) ++cnt;
						if(matrix[x][y + 1] == 1) ++cnt;
						if(matrix[x + 1][y + 1] == 1) ++cnt;
						handled[l][r] = (cnt > 1);
					}
				}
				int ans;
				in >> ans;
				this->answers.emplace_back(ans);
				std::cout << "ans  =  " << ans << "\n";
				auto hashValue = hash(handled, 14);
				std::cout << "哈希值 = " << hashValue << "\n";

				// for(int l = 0;l < 14; ++l) {
				// 	for(int r = 0;r < 14; ++r)
				// 		std::cout << handled[l][r] << " ";
				// 	std::cout << "\n";
				// }

				if(i == 1)
					break;
			}
		}
	};
}

int main() {
	YHL::KNN knn;
	knn.train();
	return 0;
}