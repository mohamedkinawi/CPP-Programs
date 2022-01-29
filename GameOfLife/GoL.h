#ifndef GOL_H
#define GOL_H

#include <vector>

namespace kinawi{

	class GOL{
		public:
			GOL();		// default constructor
			GOL(std::string absolute_path_filename) throw(std::string);
			void next_generation();
			friend std::ostream& operator<<(std::ostream& out , GOL& gol);
		private:
			bool process_line(std::ifstream& in,bool& start_determined,int& start_shift) throw(std::string);
			void perfect_grid();
			int test(int layerNum,int line,int c);
			int width;
			int height;
			int nthgeneration;
			std::vector< std::vector<int> > stacked_grids[2];
			int tabstop_mark = 8;
			const char comment_symbol = '!';
			const char rectangle_symbol = '$';
			const char cell_symbol='X';
	};

}

#endif