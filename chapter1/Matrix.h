#pragma once

#include <vector>

using namespace std;

template <typename Object>
class matrix
{
    public:
        //Normal constructor
        matrix( int rows, int cols ) : arr(rows)
        {
            for( auto& row : arr )
                row.resize( cols );
        }

        // Convertion constructors
        matrix( vector<vector<Object>> v ) : arr{ v }
        { }
        matrix( vector<vector<Object>> && v ) : arr{ std::move( v ) }
        { }

        // Operator [] overload
        const vector<Object>& operator[]( int row ) const
        { return arr[ row ]; }
        vector<Object>& operator[]( int row )
        { return arr[ row ]; }

        // Accessors
        int getRows() const
        { return arr.size(); }
        int getCols() const
        { return getRows() ? arr[0].size() : 0; }

    private:
        vector<vector<Object>> arr;
};
