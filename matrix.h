#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief       Homework project for BMEVITMJV18
 * @author      Tamás G. Barna < cremindes@sch.bme.hu >
 * @version     0.5
 */

#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief Template class Matrix represents a Matrix whose size can be
 * dynamically increased.
 */
template <typename T> class Matrix
{

public:
    /**
     * @brief matrixSize is a struct for holding a Matrix's size.
     */
    typedef struct MatrixSize {
        /**
         * @brief default constructor
         * @param row number of rows
         * @param column number of columns
         */
        MatrixSize( const unsigned& row = 0, const unsigned& column = 0 )
            : row(row), column(column) { }

        MatrixSize( const MatrixSize& size )
            : row(size.row), column(size.column) { }

        unsigned row;                   ///< number of rows
        unsigned column;                ///< number of columns

        /**
         * @brief operator <<
         * @param out output stream
         * @param size size of matrix
         * @returns the matrix's size in {row size}x{column size} format
         */
        friend std::ostream& operator<<( std::ostream& out, MatrixSize size ) {
            return out << size.row << "x" << size.column;
        }

        bool operator==( MatrixSize otherSize ) {
            return row == otherSize.row && column == otherSize.column;
        }

        bool operator!=( MatrixSize otherSize ) {
            return row != otherSize.row || column != otherSize.column;
        }
    } MatrixSize;

    /** defualt constructor */
    Matrix();

    /**
     * @brief Constructor with predefined size
     * @param rowSize number of rows
     * @param columnSize number of columns
     */
    Matrix<T>( const unsigned& rowSize, const unsigned& columnSize );

    Matrix<T>( const MatrixSize size );

    Matrix<T>( const Matrix<T>& m );

    Matrix<T>& operator=( const Matrix<T>& m )
    {
        m_size = m.size();
        dat.resize( m.size().row * m.size().column );
        for( size_t i = 0; i < dat.size(); ++i ) {
            dat[i] = m.dat[i];
        }

        return *this;
    }

    Matrix<T> operator+( const int num ) const
    {
         Matrix<T> result( m_size );

         for( size_t i = 0; i < dat.size(); ++i ) {
             result.dat[i] = dat[i] + num;
         }

         return result;
    }

    Matrix<T> operator+( const Matrix<T> m ) const
    {
        Matrix<T> result( m_size.row, m_size.column );

        if( m_size == m.size() ) {
            // elementwise addition
        } else if( m.size().row == 1 && m.size().column == m_size.column ) {
            // add to every row by element
        } else if( m.size().column == 1 && m.size().row == m_size.row ) {
            // add to every column by element
            for( size_t rowIndex = 0; rowIndex < m_size.row; ++rowIndex ) {
                for( size_t columnIndex = 0; columnIndex < m_size.column; ++columnIndex ) {
                    result.dat[ rowIndex * m_size.column + columnIndex ] = dat[ rowIndex * m_size.column + columnIndex ] + m.dat[ rowIndex ];
                }
            }
        } else {
            // error
            // TODO: throw error
            return result;
        }

        return result;
    }

    /**
     * @brief sets a new value in \a row and \a column
     * @param row row of new value
     * @param column column of new value
     * @param value new value
     * @note numbering starts from 1, not 0!
     */
    void setCell( const unsigned& row, const unsigned& column, const T& value );

    /**
     * @brief set a complete row
     * @param row row to be set
     * @param rowValues new values of row
     * @note numbering starts from 1, not 0!
     */
    void setRow( const unsigned& row, const std::vector<T>& rowValues );

    /**
     * @brief set a complete column
     * @param column column to be set
     * @param columnValues new column values
     * @note numbering starts from 1, not 0!
     */
    void setColumn( const unsigned& column, const std::vector<T>& columnValues );

    /**
     * @brief @return value of cell in \a row, \a column
     * @param row row of cell
     * @param column column of cell
     * @note numbering starts from 1, not 0!
     */
    T getCell( const unsigned& row, const unsigned& column ) const;

    /**
     * @brief @return values of a row
     * @param row row to be read
     * @note numbering starts from 1, not 0!
     */
    std::vector<T> getRow( const unsigned& row ) const;

    /**
     * @brief @return values of a column
     * @param column column to be read
     * @note numbering starts from 1, not 0!
     */
    std::vector<T> getColumn( const unsigned& column ) const;

    /**
     * @returns matrix size as a MatrixSize struct
     */
    inline MatrixSize size() const { return m_size; }

    /**
     * @returns number of rows
     */
    inline unsigned getRowSize() const { return m_size.row; }

    /**
     * @returns number of columns
     */
    inline unsigned getColumnSize() const { return m_size.column; }

    Matrix<T> rowSum() const;

    T rowSum( unsigned row ) const;


    /**
     * @brief appends \a row number rows and \a column number columns
     * to the matrix
     * @param row number of rows to append
     * @param column number of columns to append
     */
    void append( const unsigned row, const unsigned column );

    /**
     * @brief resizes matrix to {row} x {column}
     * @param row number of rows to update to
     * @param column number of columnt to update to
     */
    void resize( const unsigned row, const unsigned column );

    /**
     * @brief sets a delimiter for IO operations
     * @param newDelimiter delimiter string, e.g. ","
     */
    void setDelimiter( const std::string& newDelimiter );

    /**
     * @brief @returns the delimiter of the matrix
     */
    std::string getDelimiter() const { return delimiter; }

    /**
     * @brief operator ==
     * @param m1 matrix 1
     * @param m2 matrix 2
     * @return
     */
    friend bool operator== ( Matrix<T> &m1, Matrix<T> &m2 ) {
        if( m1.size().row    != m2.size().row   ||
            m1.size().column != m2.size().column )
        {
            return false;
        }

        for( unsigned i = 1; i <= m1.size().row; ++i ) {
            for( unsigned j = 1; j <= m1.size().column; ++j ) {
                T cell1, cell2;
                m1.getCell( i, j, cell1 );
                m2.getCell( i, j, cell2 );
                if( cell1 != cell2  ) {
                    return false;
                }
            }
        }

        return true;
    }

    /**
     * @brief operator <<  prints the whole matrix
     * @param out output stream
     * @param matrix matrix to be printed
     * @return output stream
     */
    friend std::ostream& operator <<(std::ostream& out, const Matrix<T>& matrix)
    {
        if( !matrix.dat.size() || !matrix.m_size.row || !matrix.m_size.column ) return out;

        for( unsigned row = 0; row < matrix.m_size.row; ++row ) {
            unsigned offset = row * matrix.m_size.column;
            for( unsigned column = 0; column < matrix.m_size.column; ++column ) {
                unsigned cell = offset + column;
                out << matrix.dat.at(cell)
                    << ( (cell+1) % (matrix.m_size.column) == 0 ? "" : matrix.delimiter );
            }
            out << std::endl;
        }
        return out;
    }

    /**
     * @brief operator >> read in a matrix
     * @param in input stream
     * @param matrix matrix to read into
     * @returns the input stream
     */
    friend std::istream& operator >>(std::istream& in, Matrix<T>& matrix)
    {
        unsigned rowCurrent    = 1;
        unsigned columnCurrent = 1;
        unsigned rowSize       = 1;
        unsigned columnSize    = 1;

        std::string line;
        std::getline( in, line );

        // get number of delimiters to determine the number of columns
        for ( size_t pos = line.find( matrix.delimiter );
              pos != std::string::npos;
              pos = line.find( matrix.delimiter, pos + matrix.delimiter.size() ) )
        {
            columnSize++;
        }

        // parsing rows
        while( !line.empty() ) {
            matrix.resize( rowSize, columnSize );

            unsigned pos;
            while ( !line.empty() &&
                    ( pos = line.find(matrix.delimiter) ) != std::string::npos )
            {
                std::string cell = line.substr(0, pos);
                matrix.setCell(rowCurrent, columnCurrent++, cell );
                line.erase(0, pos + matrix.delimiter.length());

                if( columnCurrent % matrix.size().column+1 == 0 ) {
                    break;
                }
            }

            columnCurrent = 1;
            rowCurrent++;
            rowSize++;

            // get new line
            std::getline( in, line );
        }

        return in;
    }

//    static friend Matrix<T> operator* (Matrix<T> &m1, Matrix<T> &m2)
//    {

//    }

    static Matrix<T> dot( const Matrix<T> &m1, const Matrix<T> &m2 )
    {
        if( m1.size().column != m2.size().row ) {
            // TODO: handle error
            return m1;
        }

        Matrix<T> result( m1.getRowSize(), m2.getColumnSize() );
        for( size_t rowIndex = 1; rowIndex <= m1.getRowSize(); ++rowIndex ) {
            for( size_t columnIndex = 1; columnIndex <= m2.getColumnSize(); ++columnIndex ) {
                double value = 0.0;
                for( unsigned i = 1; i <= m1.getColumnSize(); ++i ) {
                    value += m1.getCell( rowIndex, i ) * m2.getCell( i, columnIndex );
                }
                result.setCell( rowIndex, columnIndex, value );
            }
        }

        return result;
    }

    void apply( std::function< double (const double&, const bool&)> functionToApply, bool param )
    {
        for( size_t row = 1; row <= m_size.row; ++row ) {
            for( size_t column = 1; column <= m_size.column; ++column ) {
                setCell( row, column, functionToApply( getCell( row, column ), param ) );
            }
        }
    }

    void fill( const double& mean, const double& sd = 0 )
    {
        std::default_random_engine generator;
        std::normal_distribution<double> distribution( mean, sd );
        for( unsigned row = 1; row <= m_size.row; ++row ) {
            for( unsigned column = 1; column <= m_size.column; ++column ) {
                setCell( row, column, distribution( generator ) );
            }
        }
    }

    const Matrix<T> transpose()
    {
        Matrix<T> result( m_size.column, m_size.row );

        for( unsigned i = 1; i <= m_size.row; i++ ) {
           for( unsigned j = 1; j <= m_size.column; j++ ) {
             result.setCell( j, i, getCell( i, j ) );
           }
        }

        return result;
    }

    Matrix<T> operator/ ( const int num ) const
    {
        Matrix<T> result( m_size );

        for( size_t i = 0; i < dat.size(); ++i ) {
            result.dat[i] = dat[i] / num;
        }

        return result;
    }

    Matrix<T> operator/ ( const Matrix<T> m ) const
    {
        Matrix<T> result( m_size );

        for( size_t i = 0; i < dat.size(); ++i ) {
            result.dat[i] = dat[i] / m.dat[i];
        }

        return result;
    }

    Matrix<T> operator- ( const int num )
    {
        Matrix<T> result( m_size );

        for( size_t i = 0; i < dat.size(); ++i ) {
            result.dat[i] = dat[i] - num;
        }

        return result;
    }

    Matrix<T> operator- ( const Matrix<T> m )
    {
        Matrix<T> result( m_size );

        for( size_t i = 0; i < dat.size(); ++i ) {
            result.dat[i] = dat[i] - m.dat[i];
        }

        return result;
    }

    friend Matrix<T> operator* ( const int num, const Matrix<T>& m ) {
        Matrix<T> result( m.m_size );
        for( size_t i = 0; i < m.dat.size(); ++i ) {
            result.dat[i] = num * m.dat[i];
        }
        return result;
    }

    friend Matrix<T> operator- ( const int num, const Matrix<T>& m ) {
        Matrix<T> result( m.m_size );

        for( size_t i = 0; i < m.dat.size(); ++i ) {
            result.dat[i] = num - m.dat[i];
        }

        return result;
    }

private:

    std::vector<T> dat;         ///< matrix data
    MatrixSize m_size;          ///< size of the matrix

    std::string delimiter;      ///< delimiter string for input and output
};

template < typename T >
Matrix<T>::Matrix() : delimiter(",") { }

template < typename T >
Matrix<T>::Matrix(const unsigned& rowSize, const unsigned& columnSize) :
    m_size( rowSize, columnSize ), delimiter(",")
{
    dat.resize( rowSize * columnSize);
}

template < typename T >
Matrix<T>::Matrix( const MatrixSize size ) : m_size( size )
{
    dat.resize( size.row * size.column );
}

template < typename T >
Matrix<T>::Matrix( const Matrix<T>& m ) : m_size( m.size() )
{
    dat.resize( m.size().row * m.size().column );
    for( size_t i = 0; i < dat.size(); ++i ) {
        dat[i] = m.dat[i];
    }
}

template < typename T >
Matrix<T> operator/ ( const Matrix<T>& m, const int num )
{
    Matrix<T> result( m.size() );
    for( size_t i = 0; i < m.dat.size(); ++i ) {
        result.dat[i] = m.dat[i] / num;
    }
    return result;
}


template < typename T >
void Matrix<T>::setCell(const unsigned& row, const unsigned& column, const T& value)
{
    if( !row || !column || row > m_size.row || column > m_size.column ) {
        std::cerr << "Invalid cell (" << row << "," << column << ")!" << std::endl;
        return;
    }

    dat.at( (row-1) * m_size.column + (column-1) ) = value;
}

template < typename T >
void Matrix<T>::setRow(const unsigned& row, const std::vector<T>& rowValues)
{    
    if( row < 1 || m_size.row < row || rowValues.size() > m_size.column ) {
        std::cerr << "Invalid row or number of row values! ("
                  << row << "," << rowValues.size() << ")" << std::endl;
        return;
    }

    for( unsigned i = 0; i < rowValues.size(); ++i ) {
        unsigned cell = (row-1) * m_size.column + i;
        dat.at(cell) = rowValues.at(i);
    }
}

template < typename T >
void Matrix<T>::setColumn(const unsigned& column, const std::vector<T>& columnValues)
{
    if( 1 > column || column > m_size.column || columnValues.size() > m_size.row ) {
        std::cerr << "Invalid column or number of column values! ("
                  << column << "," << columnValues.size() << ")" << std::endl;
        return;
    }

    for( unsigned i = 0; i < columnValues.size(); ++i ) {
        unsigned cell = i * m_size.column + column;
        dat.at(cell-1) = columnValues.at(i);
    }
}

template < typename T >
T Matrix<T>::getCell(const unsigned& row, const unsigned& column ) const
{
    T res;
    try {
        res = dat.at( (row-1) * m_size.column + (column-1) );
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of range: " << oor.what() << '\n';
        res = 0.0;
    }

    return res;
}

template < typename T >
std::vector<T> Matrix<T>::getRow(const unsigned& row) const
{
    if( 1 > row || row > m_size.row ) {
        std::cerr << "Invalid row! (" << row << ")" << std::endl;
        return std::vector<T>();
    }

    std::vector<T> res( dat.begin() + (row-1) * m_size.column,
                        dat.begin() + (row-1) * m_size.column + m_size.column );
    return res;
}

template < typename T >
std::vector<T> Matrix<T>::getColumn(const unsigned& column) const
{
    if( 1 > column || column > m_size.column ) {
        std::cerr << "Invalid column! (" << column << ")" << std::endl;
        return std::vector<T>();
    }

    std::vector<T> res;
    res.reserve( m_size.column );
    for( unsigned i = 0; i < m_size.row; ++i ) {
        unsigned cell = i * m_size.column + (column-1);
        res.push_back( dat.at( cell ) );
    }

    return res;
}

template < typename T >
Matrix<T> Matrix<T>::rowSum() const
{
    Matrix<T> result( m_size.row, 1 );

    for( size_t rowIndex = 1; rowIndex <= m_size.row; ++rowIndex ) {
        for( size_t columnIndex = 1; columnIndex <= m_size.column; ++columnIndex ) {
            result.dat[rowIndex-1] += dat[ (rowIndex-1) * m_size.column + columnIndex-1 ];
        }
    }

    return result;
}

template < typename T >
T Matrix<T>::rowSum( unsigned row ) const
{
    T result = 0.0;

    for( size_t columnIndex = 1; columnIndex <= m_size.column; ++columnIndex ) {
        result += dat[ (row-1) * m_size.column + columnIndex-1 ];
    }

    return result;
}

template < typename T >
void Matrix<T>::resize(const unsigned row, const unsigned column)
{
    if( row < 1 || column < 1 ) {
        std::cerr << "Invalid row and/or column number!" << std::endl;
        return;
    }

    // resize storage
    dat.resize( row * column );

    // update size
    m_size.row    = row;
    m_size.column = column;
}

template < typename T >
void Matrix<T>::append(const unsigned row, const unsigned column)
{
    // resize storage
    dat.resize( (m_size.row + row) * (m_size.column + column) );

    // update matrix size
    m_size.row    += row;
    m_size.column += column;
}

template < typename T >
void Matrix<T>::setDelimiter( const std::string& newDelimiter )
{
    if( !newDelimiter.empty() ) {
        delimiter = newDelimiter;
    }
    else {
        std::cerr << "cannot set empty delimiter" << std::endl;
    }
}

#endif // MATRIX_H
