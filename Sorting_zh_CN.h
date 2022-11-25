/**
 * Figure 7.10
 */

template <typename Comparable>
void heapsort( vector<Comparable> & a ) /* heapsort函数，用于将一个序列中的元素进行堆排序 */
{
  /**
   * 通过使用for循环以及percDown函数来建立一个（最大）堆
   * 其中for循环从中间的元素开始对序列的元素进行遍历，直到第一个元素才结束
   * 这样便可确保后一个元素总是大于前一个元素
   */
  for( int i = a.size( ) / 2 - 1; i >= 0; --i )
    percDown( a, i, a.size( ) );  

  /**
   * 通过使用标准库里的swap函数与percDown函数依次将（最大）堆中的最大元素（第一个元素）排在最后一位
   * 可将被排在最后一位的最大元素视为不存在于堆中
   * 在这个过程中序列进行了排序
   */  
  for( int j = a.size( ) - 1; j > 0; --j )
    {
      std::swap( a[ 0 ], a[ j ] );
      percDown( a, 0, j );
    }
}

/**
   * 堆排序的内部方法
   * i为堆中某个元素的下标
   * 返回左孩子元素的下标
   */ 
inline int leftChild( int i )
{
  return 2 * i + 1;
}

/**
   * 堆排序的内部方法，在“删除”最大值和建立堆的时候会使用
   * i为开始下滤的位置
   * n为二叉堆的逻辑大小
   */ 
template <typename Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
  int child;
  Comparable tmp;


  for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child )
    {
      child = leftChild( i );
        
    
      if( child != n - 1 && a[ child ] < a[ child + 1 ] )
        ++child;
   
      if( tmp < a[ child ] )
        a[ i ] = std::move( a[ child ] );
    
      else
    break;
    }

  a[ i ] = std::move( tmp );
}

/**
 * Figure 7.11
 */

/**
 * 合并排序的算法（接口）
 */

template <typename Comparable>
void mergeSort( vector<Comparable> & a )
{
  vector<Comparable> tmpArray( a.size( ) );

  mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

/**
 * 递归调用的内部方法
 * a为数据类型为Comparable的数组
 * tmpArray为放置合并结果的数组
 * left(right)为子数组的最左（右）元素的下标
 */

template <typename Comparable>
void mergeSort( vector<Comparable> & a,
                vector<Comparable> & tmpArray, int left, int right )
{
    if( left < right )
    {
      int center = ( left + right ) / 2;
      mergeSort( a, tmpArray, left, center );
      mergeSort( a, tmpArray, center + 1, right );
      merge( a, tmpArray, left, center + 1, right );
    }
}

/**
 * Figure 7.12
 */

/**
 * 合并一个子数组的已排序的两部分的内部方法
 * a为数据类型为Comparable的数组
 * tmpArray为放置合并结果的数组
 * leftPos为子数组最左元素的下标
 * rightPos为另一半的起点的的下标
 * rightEnd为子数组最右元素的下标
 */

template <typename Comparable>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
            int leftPos, int rightPos, int rightEnd )
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    ///
    while( leftPos <= leftEnd && rightPos <= rightEnd )
        if( a[ leftPos ] <= a[ rightPos ] )
      tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );
        else
      tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    while( leftPos <= leftEnd )
        tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );

    while( rightPos <= rightEnd )
        tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    for( int i = 0; i < numElements; ++i, --rightEnd )
        a[ rightEnd ] = std::move( tmpArray[ rightEnd ] );
}

/**
 * Figure 7.13
 */

/**
 * 快速排序
 */

template <typename Comparable>
void SORT( vector<Comparable> & items )
{
if( items.size( ) > 1 )
{
vector<Comparable> smaller;
vector<Comparable> same;
vector<Comparable> larger;

auto chosenItem = items[ items.size( ) / 2 ];

for( auto & i : items )
{
if( i < chosenItem )
smaller.push_back( std::move( i ) );
else if( chosenItem < i )
larger.push_back( std::move( i ) );
else
same.push_back( std::move( i ) );
}

SORT( smaller ); // Recursive call!
SORT( larger ); // Recursive call!

std::move( begin( smaller ), end( smaller ), begin( items ) );
std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) );
std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );
}
}

/**
 * Figure 7.15
 */

/**
 * 快速排序的算法（接口）
 */

template <typename Comparable>
void quicksort( vector<Comparable> & a )
{
quicksort( a, 0, a.size( ) - 1 );
}

/**
 * Figure 7.16
 */

/**
 * 返回左侧、中间和右侧的中间值
 * 对left, center和right进行排序，并隐藏枢轴元素
 */

template <typename Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;

    if( a[ center ] < a[ left ] )
        std::swap( a[ left ], a[ center ] );
    if( a[ right ] < a[ left ] )
        std::swap( a[ left ], a[ right ] );
    if( a[ right ] < a[ center ] )
        std::swap( a[ center ], a[ right ] ); 

    std::swap( a[ center ], a[ right - 1 ] );

    return a[ right - 1 ];
}

/**
 * Figure 7.17
 */ 

/**
 * 进行递归调用的内部快速排序方法
 * 使用三数中值分割方法和10作为截止点
 * 当数组中的元素个数小于或等于10时，对该数组进行插入排序
 * 当数组中的元素个数大于10时，对该数组进行递归
 * a为数据类型为Comparable的数组
 * left(right)为子数组最左（右）元素的下标
 */

template <typename Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right );
        
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }

            while( pivot < a[ --j ] ) { }

            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );

        quicksort( a, left, i - 1 );
        quicksort( a, i + 1, right );
    }
    else
        insertionSort( a, left, right );
}