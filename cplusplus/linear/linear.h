#ifndef LINEAR_H
#define LINEAR_H

#include <iostream>
#include <stdexcept>

//	Vector


struct v // vector
{
	double x, y, z;
};


// Matrix


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

		m minor (int row, int col)
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
};


//	Vector functions


std::ostream &operator<< (std::ostream &output, const v &vec)
{
	output << vec.x << " " << vec.y << " " << vec.z;
	return output;
}


v v_add (v &v1, v &v2) // addition
{
	v result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}


v v_subtr (v &v1, v &v2) // subtraction
{
	v result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;	
}


v v_mult (double n, v &vec)	// multiplication by a constant
{
	v result;
	result.x = n * vec.x;
	result.y = n * vec.y;
	result.z = n * vec.z;
	return result;
}


double v_dot (v &v1, v &v2) // dot product
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


v v_cross (v &v1, v &v2) // cross product
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


m m_mult (m &m1, m &m2) // matrix multiplication
{
	if (m1.getCols() != m2.getRows())
	{
		throw std::runtime_error ("Wrong dimensions for matrix multiplication");
	}
	m result (m1.getRows(), m2.getCols());
	for (int i = 0; i < result.getRows(); ++i)
	{
		for (int j = 0; j < result.getCols(); ++j)
		{
			result[i][j] = 0;
			for (int k = 0; k < m1.getCols(); ++k)
			{
				result[i][j] += m1[i][k] * m2[k][j];
			}
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
					m min = mat.minor (row, i);
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
					m min = mat.minor (i, col);
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
			m min = mat.minor (i, j);
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


#endif
