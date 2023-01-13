#include "../include/matrix.h"
#if defined(MCLASS_H)


Matrix Matrix::IDENTITY(int order, bool n) {
	Matrix I;
	if (n) I = Matrix(order, order, "IDENTITY", 0); else I = Matrix(order, order, 0);
	for (int i = 0; i < I.m_rows; i++)
		I.data[i][i] = 1;
	return I;
}

Matrix Matrix::add(Matrix a) {
	Matrix A(m_rows, a.m_cols);
	A.name = name + " + " + a.name + "";
	if (m_rows == a.m_rows && m_cols == a.m_cols) {
		for (int i = 0; i < A.m_rows; i++)
			for (int j = 0; j < A.m_cols; j++)
				A.data[i][j] = data[i][j] + a.data[i][j];
	}
	else {
		throw std::invalid_argument("You can't add these two matrices (they must have the same size)");
	}
	return A;
}

Matrix Matrix::add(double a) {
	Matrix A(m_rows, m_cols);
	A.name = name + " + " + std::to_string(a);
	for (int i = 0; i < A.m_rows; i++)
		for (int j = 0; j < A.m_cols; j++)
			A.data[i][j] = data[i][j] + a;
	return A;
}

Matrix Matrix::augment(Matrix a) {
	if (a.m_rows != m_rows) {
		printf("Can't augment Matrix %s with Matrix %s (no compatible sizes)\n\n", original_name.c_str(), a.original_name.c_str());
		return *this;
	}
	Matrix A(m_rows, m_cols + a.m_cols, original_name + " | " + a.name);
	for (int i = 0; i < A.m_rows; i++) {
		for (int j = 0; j < A.m_cols; j++) {
			A.data[i][j] = (j < m_cols) ? data[i][j] : a.data[i][j - m_cols];
		}
	}
	return A;
}


Matrix Matrix::appendUp(Matrix a) {
	Matrix au = rotate(-1).augment(a.rotate(-1)).rotate(1);
	au.name = a.name + " appended to " + original_name;
	return au;
}

Matrix Matrix::appendDown(Matrix a) {
	Matrix ad = rotate(1).augment(a.rotate(1)).rotate(-1);
	ad.name = original_name;
	return ad;
}

Matrix Matrix::sub(Matrix a) {
	Matrix S(m_rows, a.m_cols);
	S.name = name + " - " + a.name;
	if (m_rows == a.m_rows && m_cols == a.m_cols) {
		for (int i = 0; i < S.m_rows; i++)
			for (int j = 0; j < S.m_cols; j++)
				S.data[i][j] = data[i][j] - a.data[i][j];
	}
	else {
		throw std::invalid_argument("You can't subtract these two matrices (they must have the same size)");
	}
	return S;
}

Matrix Matrix::sub(double a) {
	Matrix S(m_rows, m_cols);
	S.name = name + " - " + std::to_string(a);
	for (int i = 0; i < S.m_rows; i++)
		for (int j = 0; j < S.m_cols; j++)
			S.data[i][j] = data[i][j] - a;
	return S;
}

Matrix Matrix::mult(Matrix a) {
	Matrix P(m_rows, a.m_cols);
	P.name = name + " x " + a.name;
	if (m_rows == 1 && m_cols == 1) {
		Matrix P = a;
		P.name = name + " x " + a.name;
		for (int i = 0; i < P.m_rows; i++)
			for (int j = 0; j < P.m_cols; j++)
				P.data[i][j] *= data[0][0];
		return P;
	}
	else if (m_cols != a.m_rows) {
		throw std::invalid_argument("You Can't Multiply These two matrices");
	}
	else {
		for (int i = 0; i < P.m_rows; i++)
			for (int j = 0; j < P.m_cols; j++)
				for (int k = 0; k < a.m_rows; k++)
					P.data[i][j] += data[i][k] * a.data[k][j];
	}
	return P;
}

Matrix Matrix::mult(double a) {
	Matrix P = *this;
	for (int i = 0; i < P.m_rows; i++)
		for (int j = 0; j < P.m_cols; j++)
			P.data[i][j] *= a;
	return P;
}

Matrix Matrix::div(Matrix a) {
	return this->mult(a.inverse());
}
Matrix Matrix::div(double a) {
	return this->mult(1 / a);
}

Matrix Matrix::transpose() {
	Matrix t(m_cols, m_rows);
	t.name += " transposed";
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
			t.data[j][i] = data[i][j];
	return t;
}

Matrix Matrix::rotate(int dir) {
	Matrix R = *this;

	if (dir % 4 == 0)
		return *this;
	else if (dir > 0) {
		for (int z = 0; z < dir % 4; z++) {
			R = R.transpose();
			for (int i = 0; i < R.m_cols; i++)
				for (int j = 0, k = R.m_rows - 1; j < k; j++, k--)
					std::swap(R.data[j][i], R.data[k][i]);
		}
		R.name = name + " rotated anti-clockwise " + std::to_string(dir) + " time";
		R.name += (abs(dir) > 1) ? "s" : "";
		return R;
	}
	else if (dir < 0) {
		dir *= -1;
		for (int z = 0; z < dir % 4; z++) {
			R = R.transpose();
			for (int i = 0; i < R.m_rows; i++)
				for (int j = 0, k = R.m_cols - 1; j < k; j++, k--)
					std::swap(R.data[i][j], R.data[i][k]);
		}
		R.name = name + " rotated clockwise " + std::to_string(dir) + " time";
		R.name += (abs(dir) > 1) ? "s" : "";
		return R;
	}
	return *this;
}


Matrix Matrix::minor(int i_, int j_) {
	i_--;
	j_--;
	if (i_ > m_rows - 1 || j_ > m_cols - 1) {
		std::string error = "Element of index [" + std::to_string(i_ + 1) + ", " + std::to_string(j_ + 1) + "] is outside the matrix range ";
		throw std::invalid_argument(error);
	}
	_2DVector _m;
	_m.data = data;
	Matrix m = Matrix(m_rows - 1, m_cols - 1, "Minor Matrix", 0);
	m.data = _2DVector::clrRowColumn(_m, i_, j_).data;
	return m;
}


Matrix Matrix::inverse() {
	Matrix temp = *this;
	double det = 1;

	try
	{
		det = Matrix::determ(temp);
	}
	catch (const std::exception& e) {}

	if (m_rows != m_cols) {
		throw std::invalid_argument("Non-square matrices can't be inverted!");
	}
	else if (det == 0) {
		printf("\nThere is no inverse to the Matrix:%s[%d x %d] (determinant is ZERO)\n", original_name.c_str(), m_rows, m_cols);
		return *this;
	}
	else {
		if (temp.m_rows == 1) {
			if (temp.data[0][0] != 0)
				temp.data[0][0] = 1 / temp.data[0][0];
			temp.name += " inversed";
			return temp;
		}
		else if (temp.m_rows == 2) {
			temp.name += " inversed";
			std::swap(temp.data[0][0], temp.data[1][1]);
			temp.data[0][1] *= -1;
			temp.data[1][0] *= -1;
			for (int i = 0; i < temp.m_rows; i++)
				for (int j = 0; j < temp.m_cols; j++)
					temp.data[i][j] /= det;
			return temp;
		}
		else {
			// Gauss-Jordan:

			Matrix aug = temp.augment(Matrix::IDENTITY(temp.m_rows, false));
			temp.name = name + " inversed";
			for (int i = temp.m_rows - 1; i > 0; i--) {
				if (aug.data[i - 1][0] < aug.data[i][0]) {
					swap(aug.data[i], aug.data[i - 1]);
				}
			}
			for (int i = 0; i < temp.m_rows; i++) {
				for (int j = 0; j < temp.m_cols; j++) {
					if (j != i) {
						double t = aug.data[j][i] / aug.data[i][i];
						for (int k = 0; k < aug.m_cols; k++) {
							aug.data[j][k] -= aug.data[i][k] * t;
						}
					}
				}
			}
			for (int i = 0; i < temp.m_rows; i++) {
				double t = aug.data[i][i];
				for (int j = 0; j < aug.m_cols; j++) {
					aug.data[i][j] /= t;
				}
			}
			for (int i = 0; i < temp.m_rows; i++) {
				for (int j = 0; j < temp.m_cols; j++) {
					temp.data[i][j] = aug.data[i][j + temp.m_cols];
				}
			}
			return temp;

			// Minors, Cofactors:


			// Matrix adj = temp;
			// adj.name = name + " inversed";
			// adj = adj.transpose();
			// _2DVector t;
			// t.data = adj.data;
			// for (int i = 0; i < adj.m_rows; i++)
			// 	for (int j = 0; j < adj.m_cols; j++) {
			// 		// Matrix min = adj.minor(i + 1, j + 1);
			// 		t.data[i][j] = Matrix::determ(Matrix::minor(adj, i + 1, j + 1)) * pow(-1, i + j) / det;
			// 	}
			// adj.data = t.data;
			// adj.name = adj.name.substr(0, 10);
			// return adj;
		}
	}
}



double Matrix::determ() {
	double  det = 0;
	Matrix temp = *this;
	if (m_rows != m_cols) {
		throw std::invalid_argument("Non-square matrices don't have a determinant");
	}
	else if (m_rows == 1)
		return data[0][0];
	else if (m_rows == 2)
		det = (data[0][0] * data[1][1]) -
		(data[0][1] * data[1][0]);
	else {
		bool degen = false;
		det = 1;
		for (int i = 0; i < m_rows; i++) {
			degen = !(data[i][i]);
			if (degen) break; else continue;
		}
		if (degen) {
			for (int i = temp.m_rows - 1; i > 0; i--) {
				if (temp.data[i - 1][0] < temp.data[i][0]) {
					swap(temp.data[i], temp.data[i - 1]);
					det *= -1;
				}
			}
		}

		for (int i = 0; i < m_rows; i++) {
			for (int k = i + 1; k < m_rows; k++) {
				if (temp.data[i][i] == 0) return 0;
				double m = temp.data[k][i] / temp.data[i][i];
				for (int j = 0; j < m_cols; j++) {
					temp.data[k][j] -= m * temp.data[i][j];
				}
			}
		}
		for (int i = 0; i < m_rows; i++)
			det *= temp.data[i][i];

		// for (int i = 0; i < m_rows; i++)
		// 	det += temp.minor(1, i + 1).determ() * temp.data[0][i] * pow(-1, i);
	}
	return det;
}

Matrix Matrix::power(int n) {
	if (m_cols != m_rows) {
		throw std::invalid_argument("Power is only for square Matrices");
	}
	else {
		Matrix temp = *this;
		Matrix P = *this;
		for (int i = 0; i < n - 1; i++)
			P = P.mult(temp);
		return P;
	}
}


void Matrix::print() {
	color(FOREGROUND_GREEN);
	if (m_rows == 1 && m_cols == 1) {
		printf("Scalar (%s):\n", name.c_str());
		color(FOREGROUND_BLUE);
		printf("[%.3f]\n\n", data[0][0]);
		color(FOREGROUND_REGULAR);
		return;
	}
	else if (m_rows == 1 || m_cols == 1) {
		printf("Vector ( %s )[%dx%d] is:  \n\n", name.c_str(), m_rows, m_cols);
	}
	else {
		printf("Matrix ( %s )[%dx%d] is:  \n\n", name.c_str(), m_rows, m_cols);
	}
	color(FOREGROUND_BLUE);
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (m_cols == 1 && m_rows == 1)
				continue;
			else if (m_cols == 1) {
				if (i == 0 && m_rows > 1)
					printf("%s  %.3f  %s", UL_BRACKET, data[i][j], UR_BRACKET);

				else if (i == m_rows - 1 && m_rows > 1)
					printf("%s  %.3f  %s", BL_BRACKET, data[i][j], BR_BRACKET);
				else {
					printf("|  %.3f  |", data[i][j]);
				}
			}
			else {
				if (j == m_cols - 1) {
					if (i == 0 && m_rows > 1)
						printf("%.3f\t %s", data[i][j], UR_BRACKET);
					else if (i == m_rows - 1 && m_rows > 1)
						printf("%.3f\t %s", data[i][j], BR_BRACKET);
					else if (m_rows == 1)
						printf("%.3f\t]", data[i][j]);
					else if (m_rows > 1)
						printf("%.3f\t |", data[i][j]);
				}
				else if (j == 0) {
					if (i == 0 && m_rows > 1)
						printf("%s\t %.3f\t", UL_BRACKET, data[i][j]);
					else if (i == m_rows - 1 && m_rows > 1)
						printf("%s\t %.3f\t", BL_BRACKET, data[i][j]);

					else if (m_rows == 1)
						printf("[\t%.3f\t", data[i][j]);
					else
						printf("|\t %.3f\t", data[i][j]);

				}
				else
					printf("%.3f\t", data[i][j]);

			}
		}
		printf("\n");
	}
	printf("\n\n\n");
	color(FOREGROUND_REGULAR);
}

void Matrix::input() {
	printf("Input elements for Matrix %s [%d x %d]=> \n", name.c_str(), m_rows, m_cols);
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			printf("Enter element [%d,%d]: ", i + 1, j + 1);
			std::cin >> data[i][j];
			scanf("", &data[i][j]);
		}
	}
	printf("\n");
	if (m_cols == 1 && m_rows == 1)
		name = std::to_string(data[0][0]);
}


void Matrix::fill_random(int a, int b) {
	srand(time(NULL) * rand());
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++)
			data[i][j] = randomDouble(a, b);
	}
	if (m_cols == 1 && m_rows == 1)
		name = std::to_string(data[0][0]);
}

void Matrix::fill_random_int(int a, int b) {
	srand(time(NULL) * rand());
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
			data[i][j] = (int)randomDouble(a, b);
	if (m_cols == 1 && m_rows == 1)
		name = std::to_string(data[0][0]);

}

double Matrix::randomDouble(double a, double b) {
	double random = ((double)rand()) / (double)RAND_MAX;
	double diff = b - a;
	double r = random * diff;
	return a + r;
}


#endif // MATRIX_H