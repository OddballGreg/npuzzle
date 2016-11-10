<?php

class Node
{
	private $_hash;
	private $_grid;
	private $_parent;
	private $_id;
	private $_size;
	private $_cost;
	private $_emptyxy = array('x' => 0, 'y' => 0);

	public function __construct($id, $parent, $hash, $size)
	{
		$this->_id = $id;
		$this->_parent = $parent;
		$this->_size = $size;

		$this->_hash = $hash;
		$this->_grid = explode(",", $hash);
		$x = -1;
		foreach ($this->_grid as $row)
			$this->_grid[++$x] = explode(" ", $row);

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
		return ("ID: {$this->_id}\t\tHash: {$this->_hash} ");
	}

	public function hash()
	{
		return ($this->_hash);
	}

	public function move()
	{
		
	}

	public function setGoal()
	{
		$x = 0;
		$y = -1; 
		$dir = 1;
		$count = 0;
		while (isset($this->_grid[$x]))
		{
			while (isset($this->_grid[$x][$y = $y + $dir]))
				$this->_grid[$x][$y] = $count++;
			if ($dir == 1)
				$dir = -1;
			else
				$dir = 1;
			$x++;
		}
		foreach ($this->_grid as $row)
			$prehash[] = implode(" ", $row);
		$this->_hash = implode(",", $prehash);
	}
}


?>