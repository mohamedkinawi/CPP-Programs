#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "GoL.h"

namespace kinawi{
	
	GOL::GOL(){ // default constructor
		
	}
	GOL::GOL(string absolute_path_filename) throw(string){
		ifstream in;
		in.open(absolute_path_filename);
		if(in.fail()){
			throw("Failed to open the file!");
		}
		bool start_determined = false;
		int start_shift;
		while(process_line(in,start_determined,start_shift));
		in.close();
		nthgeneration=1;
		perfect_grid();
	}
	void GOL::next_generation(){
		int originalgrid = nthgeneration%2;
		int othergrid = !originalgrid;
		for(unsigned int line=0;line<height;line++){
			for(unsigned int c=0;c<width;c++){
				stacked_grids[othergrid][line][c] = test(originalgrid,line,c);
			}
		}
		nthgeneration++;
	}
	ostream& operator<<(ostream& out , kinawi::GOL& gol){
		for(unsigned int line=0;line<gol.height;line++){
			for(unsigned int c=0;c<gol.width;c++){
				if(gol.stacked_grids[gol.nthgeneration%2][line][c]==0)
					out<<' ';
				else
					out<<gol.cell_symbol;
			}
			out<<endl;
		}
		out<<"This is generation number "<<gol.nthgeneration<<endl;
		return out;
	}
	bool GOL::process_line(ifstream& in,bool& start_determined,int& start_shift) throw(string){
		char next;
		int x_absolute_steps = 0;
		int spacebuffer=0;
		bool comment = false;
		bool this_line_start_determined = false;
		bool dimensions_determined = false;
		vector<int> line;
		while((spacebuffer && spacebuffer--) || (!(in.get(next).eof()) && next!='\n')){
			if(comment){
				continue;
			}
			else if(next==comment_symbol){
				comment = true;
				if(this_line_start_determined){
					start_determined = false;
				}
				dimensions_determined = false;
			}
			else if(next==rectangle_symbol && !dimensions_determined){
				x_absolute_steps++;
				line.push_back(0);
				if(!start_determined){
					this_line_start_determined = true;
					start_determined = true;
					start_shift = x_absolute_steps;
				}
				else{
					dimensions_determined = true;
					width = line.size();
					height = stacked_grids[1].size()+1;
				}
			}
			else if(!dimensions_determined){
				if(next=='\t'){
					spacebuffer = tabstop_mark-(x_absolute_steps%tabstop_mark);
					next = ' ';
				}
				else{
					x_absolute_steps++;
					if(start_determined && x_absolute_steps>=start_shift){
						if(next==cell_symbol) line.push_back(1);
						else line.push_back(0);
					}
				}
			}
		}
		if(!comment) stacked_grids[1].push_back(line);
		if(in.eof()){
			if(!start_determined) throw(string("Failed to find a valid '$' symbol for the left upper corner of the grid"));
			else if(!dimensions_determined) throw(string("Failed to find a valid '$' symbol for the lower right corner of the grid"));
			else return 0;
		}
		else{
			if(dimensions_determined) return 0;
			else return 1;
		}
	}
	void GOL::perfect_grid(){
		for(unsigned int line = 0 ; line < height ; line++ ){
			stacked_grids[1][line].resize(width);
		}
		stacked_grids[0] = stacked_grids[1];
	}
	int GOL::test(int layerNum,int line,int c){
		int cell = stacked_grids[layerNum][line][c];
		int count = 0;
		for (int row = -1; row <= 1; row++) {
			for (int col = -1; col <= 1; col++) {
				if (line+row<height && line+row>=0 && c+col<width && c+col>=0 && stacked_grids[layerNum][line + row][c + col] != 0)
					count++;
			}
		}
		if (!cell) {
			if (count == 3)
				return 1;
			else
				return 0;
		}
		else {
			if (count == 3 || count == 4)
				return ++cell;
			else
				return 0;
		}
	}
}
