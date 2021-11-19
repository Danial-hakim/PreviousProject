#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Cell
{
public:

	/// Set the m_isPassable to true or false depending on the bool return 
	void setPassable(bool t_isPassable);

	/// Set the Id of the cell
	void setId(int Id);

	/// Get the centre point of the cell
	void setCentre(sf::Vector2f t_centre);

	/// Set the mark to true if the algorithm have found the cell
	void setMarked(bool t_isMarked);

	/// Add the neighbours to the cell
	void addNeighbours(int t_cellId);

	/// return a list of neighbours
	std::vector<int>& neighbours();

	/// return the id of the ell
	int id();

	/// check if the cell is marked
	bool isMarked() const;

	/// get the parent cell of the current cell
	int previous() const;

	/// set the parent cell of the current cell
	void setPrevious(int t_previous);

	/// return the x and y positon of the cell
	sf::Vector2f getPosition();

	/// check if the cell has obstacle on it 
	bool getPassable() const;

private:

	int m_id; // the id of the cell
	int m_previousCellId{ -1 }; // the parent id
	bool m_marked; // if mark is false , the algorithm have not reach this cell 
	bool m_isPassable{ true }; // if passable is false , there is a sprite/rectangle on the cell 

	int m_centreX; // the centre of the cell on x axis
	int m_centreY; // the centre of the cell on y axis

	std::vector<int> m_neighbours; //the cells around the current cell 
};
