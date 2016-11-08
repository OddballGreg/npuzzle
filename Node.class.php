<?php

class Node
{
	private $_hash;
	private $_grid;
	private $_parent;
	private $_id;
	private $_emptyxy = array('x' => 0, 'y' => 0);

	public function __construct($id, $parent, $hash)
	{
		$this->_id = $id;
		$this->_parent = $parent;

		$this->_hash = $hash;
		$this->_grid = explode(",", $hash);
		foreach ($this->_grid as $row)
			$row = explode(" ", $row);

		$x = -1;
		while (isset($this->_grid[++$x]))
		{
			$y = -1;
			while (isset($this->_grid[$x][++$y]))
				if ($this->_grid[$x][$y] == '0')
				{
					$this->_emptyxy['x'] = $x;
					$this->_emptyxy['y'] = $y;
				}
		}
	}

	public function __ToString()
	{
		return ($this->_id);
	}

	public function gethash()
	{
		return ($this->_hash);
	}

	public function move()
	{
		
	}

}


?>