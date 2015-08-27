#ifndef LINEAR_H
#define LINEAR_H

#include <iostream>
#include <stdexcept>
#include <cmath>

#define PI 3.14159265

//	Classes

struct v // vector
{
	double x, y, z;
	v &operator+= (const v &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}

	v &operator-= (const v &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}
};


inline v operator+ (v lhs, const v &rhs)
{
	lhs += rhs;
	return lhs;
}


inline v operator- (v lhs, const v &rhs)
{
	lhs -= rhs;
	return lhs;
}


std::ostream &operator<< (std::ostream &output, const v &vec)
{
	output << vec.x << " " << vec.y << " " << vec.z;
	return output;
}


class m // matrix
{
	private:

		double **matrix;
		int nrows, ncols;

	public:

		class p
		{
			private:
				double *arr;

			public:
				p (double *a)
					:	arr (a)
				{
				}

				double &operator[] (int c)
				{
					return this->arr[c];
				}
		};


		m (int nrows, int ncols)
		{
			this->matrix = new double *[nrows];
			for (int i = 0; i < nrows; ++i)
			{
				this->matrix[i] = new double [ncols];
				for (int j = 0; j < ncols; ++j)
				{
					this->matrix[i][j] = 0;
				}
			}
			this->nrows = nrows;
			this->ncols = ncols;
		}

		~m()
		{
			for (int i = 0; i < this->nrows; ++i)
			{
				delete [] this->matrix[i];
			}
			delete this->matrix;
		}


		m (const m &m2)
		{
			this->nrows = m2.nrows;
			this->ncols = m2.ncols;
			this->matrix = new double *[this->nrows];
			for (int i = 0; i < nrows; ++i)
			{
				this->matrix[i] = new double [this->ncols];
				for (int j = 0; j < ncols; ++j)
				{
					this->matrix[i][j] = m2.matrix[i][j];
				}
			}
		}

		void assign (int r, int c, double v)
		{
			this->matrix[r][c] = v;
		}


		p operator[] (int r) const
		{
			return p (this->matrix[r]);
		}

		

		int getRows() const
		{
			return this->nrows;
		}


		int getCols() const
		{
			return this->ncols;
		}

		m min (int row, int col)
		{
			if (this->nrows < 2 || this->ncols < 2)
			{
				throw std::runtime_error ("Matrix too small to take minor");
			}
			m result (this->nrows - 1, this->ncols - 1);
			for (int i = 0; i < result.getRows(); ++i)
			{
				for (int j = 0; j < result.getCols(); ++j)
				{
					if (i < row)
					{
						if (j < col)
						{
							result[i][j] = this->matrix[i][j];
						}
						else
						{
							result[i][j] = this->matrix[i][j + 1];
						}
					}
					else
					{
						if (j < col)
						{
							result[i][j] = this->matrix[i + 1][j];
						}
						else
						{
							result[i][j] = this->matrix[i + 1][j + 1];
						}
					}
				}
			}
			return result;
		}

		friend void swap (m &m1, m &m2);

		m &operator= (m rhs)
		{
			swap (*this, rhs);
			return *this;
		}


		m &operator+= (const m &rhs)
		{
			if ((this->nrows != rhs.nrows) || (this->ncols != rhs.ncols))
			{
				throw std::runtime_error ("Matrices with different dimensions cannot be added");
			}
			for (int i = 0; i < this->nrows; ++i)
			{
				for (int j = 0; j < this->ncols; ++j)
				{
					this->matrix[i][j] += rhs.matrix[i][j];
				}
			}
			return *this;
		}


		m &operator-= (const m &rhs)
		{
			if ((this->nrows != rhs.nrows) || (this->ncols != rhs.ncols))
			{
				throw std::runtime_error ("Matrices with different dimensions cannot be added");
			}
			for (int i = 0; i < this->nrows; ++i)
			{
				for (int j = 0; j < this->ncols; ++j)
				{
					this->matrix[i][j] -= rhs.matrix[i][j];
				}
			}
			return *this;
		}

		m operator* (const m &rhs) // matrix multiplication
		{
			if (this->ncols != rhs.nrows)
			{
				throw std::runtime_error ("Wrong dimensions for matrix multiplication");
			}
			m result (this->nrows, rhs.ncols);
			for (int i = 0; i < this->nrows; ++i)
			{
				for (int j = 0; j < rhs.ncols; ++j)
				{
					result[i][j] = 0;
					for (int k = 0; k < this->ncols; ++k)
					{
						result[i][j] += this->matrix[i][k] * rhs.matrix[k][j];
					}
				}
			}
			return result;
		}
};


void swap (m &m1, m &m2)
{
	double **temp = m1.matrix;
	int tempR, tempC;
	tempR = m1.nrows;
	tempC = m1.ncols;
	m1.matrix = m2.matrix;
	m2.matrix = temp;
	m1.nrows = m2.nrows;
	m1.ncols = m2.ncols;
	m2.nrows = tempR;
	m2.ncols = tempC;
}


inline m operator+ (m lhs, const m &rhs)
{
	lhs += rhs;
	return lhs;
}


inline m operator- (m lhs, const m &rhs)
{
	lhs -= rhs;
	return lhs;
}


std::ostream &operator<< (std::ostream &output, const m &mat)
{
	output << mat[0][0];
	for (int i = 1; i < mat.getCols(); ++i)
	{
		output << " " << mat[0][i];
	}
	for (int i = 1; i < mat.getRows(); ++i)
	{
		output << "\n";
		output << mat[i][0];
		for (int j = 1; j < mat.getCols(); ++j)
		{
			output << " " << mat[i][j];
		}
	}
	return output;
}


//	Vector functions


v c_mult (double n, v &vec)	// multiplication by a constant
{
	v result;
	result.x = n * vec.x;
	result.y = n * vec.y;
	result.z = n * vec.z;
	return result;
}


double dot (v &v1, v &v2) // dot product
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


v cross (v &v1, v &v2) // cross product
{
	v result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}


v lerp (v &v1, v &v2, double beta) // linear interpolation (0 <= beta <= 1)
{
	if ((beta < 0) || (beta > 1))
	{
		throw std::runtime_error ("Beta not in range");
	}
	
}


//	Matrix functions


m m_trans (m &m1)
{
	m result (m1.getCols(), m1.getRows());
	for (int i = 0; i < result.getRows(); ++i)
	{
		for (int j = 0; j < result.getCols(); ++j)
		{
			result[i][j] = m1[j][i];
		}
	}
	return result;
}


double m_det (m &mat) // matrix determinant
{
	if (mat.getRows() != mat.getCols())
	{
		throw std::runtime_error ("Non square matrices do not have determinant");
	}
	if (mat.getRows() == 2)
	{
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	}
	else
	{
		double result = 0;
		int zeros = 0;
		int row = -1;
		int col = -1;
		for (int i = 0; i < mat.getRows(); ++i)
		{
			int temp = 0;
			for (int j = 0; j < mat.getCols(); ++j)
			{
				if (mat[i][j] == 0)
				{
					++temp;
				}
			}
			if (temp > zeros)
			{
				zeros = temp;
				row = i;
			}
		}
		for (int i = 0; i < mat.getCols(); ++i)
		{
			int temp = 0;
			for (int j = 0; j < mat.getRows(); ++j)
			{
				if (mat[j][i] == 0)
				{
					++temp;
				}
			}
			if (temp > zeros)
			{
				zeros = temp;
				row = -1;
				col = i;
			}
		}
		if (row != -1)
		{
			for (int i = 0; i < mat.getCols(); ++i)
			{
				if (mat[row][i] != 0)
				{
					m min = mat.min (row, i);
					if ((row + 1 + i + 1) % 2)
					{
						result += (-1) * mat[row][i] * m_det (min);
					}
					else
					{
						result += mat[row][i] * m_det (min);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < mat.getRows(); ++i)
			{
				if (mat[i][col] != 0)
				{
					m min = mat.min (i, col);
					if ((i + 1 + col + 1) % 2)
					{
						result += (-1) * mat[i][col] * m_det (min);
					}
					else
					{
						result += mat[i][col] * m_det (min);
					}
				}
			}			
		}
		return result;
	}
}


m m_inv (m &mat) // inverse of a matrix
{
	if (mat.getRows() != mat.getCols())
	{
		throw std::runtime_error ("Non square matrices cannot be inverted");
	}
	double det = m_det (mat);
	if (!det)
	{
		throw std::runtime_error ("Zero determinant square matrices cannot be inverted");
	}
	m result (mat.getRows(), mat.getCols());
	for (int i = 0; i < result.getRows(); ++i)
	{
		for (int j = 0; j < result.getCols(); ++j)
		{
			m min = mat.min (i, j);
			if ((i + 1 + j + 1) % 2)
			{
				result[i][j] = (-1) * m_det (min) / det;
			}
			else
			{
				result[i][j] = m_det (min) / det;
			}
		}
	}
	return m_trans (result);
}


//	Point

struct p // point and its transformations
{
	double x, y, z;

	p &operator+= (const p &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}



	p &operator-= (const p &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}


	void translate (v &vec) // translate a point by a vector v
	{
		m point (1, 4);
		point[0][0] = this->x;
		point[0][1] = this->y;
		point[0][2] = this->z;
		point[0][3] = 1;
		m trMat (4, 4);
		trMat[0][0] = trMat[1][1] = trMat[2][2] = trMat[3][3] = 1;
		trMat[3][0] = vec.x;
		trMat[3][1] = vec.y;
		trMat[3][2] = vec.z;
		m result = point * trMat;
		this->x = result[0][0];
		this->y = result[0][1];
		this->z = result[0][2];
	}

	void rotate_x (double a) // rotate a point about x-axis by angle a
	{
		m point (1, 4);
		point[0][0] = this->x;
		point[0][1] = this->y;
		point[0][2] = this->z;
		point[0][3] = 1;
		m trMat (4, 4);
		trMat[0][0] = trMat[3][3] = 1;
		trMat[1][1] = trMat[2][2] = std::cos (a * PI / 180.0);
		trMat[1][2] = std::sin (a * PI / 180.0);
		trMat[2][1] = (-1.0) * std::sin (a * PI / 180.0);
		m result = point * trMat;
		this->x = result[0][0];
		this->y = result[0][1];
		this->z = result[0][2];
	}


	void rotate_y (double a) // rotate a point about y-axis by angle a
	{
		m point (1, 4);
		point[0][0] = this->x;
		point[0][1] = this->y;
		point[0][2] = this->z;
		point[0][3] = 1;
		m trMat (4, 4);
		trMat[1][1] = trMat[3][3] = 1;
		trMat[0][0] = trMat[2][2] = std::cos (a * PI / 180.0);
		trMat[2][0] = std::sin (a * PI / 180.0);
		trMat[0][2] = (-1.0) * std::sin (a * PI / 180.0);
		m result = point * trMat;
		this->x = result[0][0];
		this->y = result[0][1];
		this->z = result[0][2];
	}


	void rotate_z (double a) // rotate a point about y-axis by angle a
	{
		m point (1, 4);
		point[0][0] = this->x;
		point[0][1] = this->y;
		point[0][2] = this->z;
		point[0][3] = 1;
		m trMat (4, 4);
		trMat[2][2] = trMat[3][3] = 1;
		trMat[0][0] = trMat[1][1] = std::cos (a * PI / 180.0);
		trMat[0][1] = std::sin (a * PI / 180.0);
		trMat[1][0] = (-1.0) * std::sin (a * PI / 180.0);
		m result = point * trMat;
		this->x = result[0][0];
		this->y = result[0][1];
		this->z = result[0][2];
	}


	void scale (int s_x, int s_y, int s_z)
	{
		m point (1, 4);
		point[0][0] = this->x;
		point[0][1] = this->y;
		point[0][2] = this->z;
		point[0][3] = 1;
		m trMat (4, 4);
		trMat[0][0] = s_x;
		trMat[1][1] = s_y;
		trMat[2][2] = s_z;
		trMat[3][3] = 1;
		m result = point * trMat;
		this->x = result[0][0];
		this->y = result[0][1];
		this->z = result[0][2];		
	}
};


inline p operator+ (p lhs, const p &rhs)
{
	lhs += rhs;
	return lhs;
}


inline p operator- (p lhs, const p &rhs)
{
	lhs -= rhs;
	return lhs;
}


std::ostream &operator<< (std::ostream &output, const p &point)
{
	output << point.x << " " << point.y << " " << point.z;
	return output;
}


#endif
