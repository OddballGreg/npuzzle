<?php

class Node
{
	private $_parentHash;
	private $_hash;
	private $_grid;
	private $_parent;
	private $_id;
	private $_size;
	private $_dist;
	private $_estcost;
	private $_emptyxy = array('x' => 0, 'y' => 0);

	public function __construct($id, $parent, $hash, $size, $dist, $parentHash)
	{
		$this->_id = $id;
		$this->_parent = $parent;
		$this->_size = $size;
		$this->_dist = $dist;
		$this->_parentHash = $parentHash;

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

		if ($this->_id != "sol" && $this->_id != 0)
		{
			$this->setCost(); // Cost setting is dependent on the solution existing. The solution is derived from the initial state.
			$GLOBALS['uhash'][] = $this->_hash;
		}
	}

	public function __ToString()
	{
		return ("ID: " . str_pad($this->_id, 6) . "\tHash: {$this->_hash}\tDistance Travelled: " . str_pad($this->_dist, 3) . "\tEstCost: " . 
		str_pad($this->_estcost, 3) . "\tFofX: "  . str_pad($this->_estcost + $this->_dist, 3) . "\tParentID: " . str_pad($this->_parent, 6));
	}

	public function getHash()
	{
		return ($this->_hash);
	}

	public function getGrid()
	{
		return ($this->_grid);
	}

	public function getParent()
	{
		return ($this->_parent);
	}

	public function getId()
	{
		return ($this->_id);
	}

	public function getFofX()
	{
		return ($this->_dist + $this->_estcost);
	}

	public function getCost()
	{
		return ($this->_estcost);
	}

	public function setCost($cost = NULL)
	{
		if ($cost != NULL)
			$this->_estcost = $cost;
		else
		{
			if ($GLOBALS['hstc'] == MANHATTAN)
				$this->_estcost = manhattan($this, $GLOBALS['sol']);
			else if ($GLOBALS['hstc'] == EUCLIDEAN)
				$this->_estcost = euclidean($this, $GLOBALS['sol']);
			else
				$this->_estcost = hamming($this, $GLOBALS['sol']);
		}
	}

	public function genMoves()
	{
		$moves = array();
		$grid = $this->_grid;
		if (isset( $grid [$this->_emptyxy['x'] + 1] [$this->_emptyxy['y']] ))
		{
			$temp = $grid [$this->_emptyxy['x'] + 1] [$this->_emptyxy['y']];
			$grid [$this->_emptyxy['x'] + 1] [$this->_emptyxy['y']] = $grid [$this->_emptyxy['x']] [$this->_emptyxy['y']];
			$grid [$this->_emptyxy['x']] [$this->_emptyxy['y']] = $temp;
			$hash = $this->makeHash($grid);
            $check = FALSE;
            if (in_array($this->_hash, $GLOBALS['uhash']))
				$check = TRUE;
			if (strcmp($this->_parentHash, $hash) !== 0 && $check == FALSE)
				$moves[] = new Node($GLOBALS['idc']++, $this->_id, $hash, $GLOBALS['size'], $this->_dist + 1, $this->_hash);
		}
		$grid = $this->_grid;
		if (isset( $grid [$this->_emptyxy['x'] - 1] [$this->_emptyxy['y']] ))
		{
			$temp = $grid [$this->_emptyxy['x'] - 1] [$this->_emptyxy['y']];
			$grid [$this->_emptyxy['x'] - 1] [$this->_emptyxy['y']] = $grid [$this->_emptyxy['x']] [$this->_emptyxy['y']];
			$grid [$this->_emptyxy['x']] [$this->_emptyxy['y']] = $temp;
			$hash = $this->makeHash($grid);
            $check = FALSE;
            if (in_array($this->_hash, $GLOBALS['uhash']))
				$check = TRUE;
			if (strcmp($this->_parentHash, $hash) !== 0 && $check == FALSE)
				$moves[] = new Node($GLOBALS['idc']++, $this->_id, $hash, $GLOBALS['size'], $this->_dist + 1, $this->_hash);
		}
		$grid = $this->_grid;
		if (isset( $grid [$this->_emptyxy['x']] [$this->_emptyxy['y'] + 1] ))
		{
			$temp = $grid [$this->_emptyxy['x']] [$this->_emptyxy['y']  + 1];
			$grid [$this->_emptyxy['x']] [$this->_emptyxy['y']  + 1] = $grid [$this->_emptyxy['x']] [$this->_emptyxy['y']];
			$grid [$this->_emptyxy['x']] [$this->_emptyxy['y']] = $temp;
			$hash = $this->makeHash($grid);
            $check = FALSE;
            if (in_array($this->_hash, $GLOBALS['uhash']))
				$check = TRUE;
			if (strcmp($this->_parentHash, $hash) !== 0 && $check == FALSE)
				$moves[] = new Node($GLOBALS['idc']++, $this->_id, $hash, $GLOBALS['size'], $this->_dist + 1, $this->_hash);
		}
		$grid = $this->_grid;
		if (isset( $grid [$this->_emptyxy['x']] [$this->_emptyxy['y'] - 1] ))
		{
			$temp = $grid [$this->_emptyxy['x']] [$this->_emptyxy['y'] - 1];
			$grid [$this->_emptyxy['x']] [$this->_emptyxy['y']  - 1] = $grid [$this->_emptyxy['x']] [$this->_emptyxy['y']];
			$grid [$this->_emptyxy['x']] [$this->_emptyxy['y']] = $temp;
            $hash = $this->makeHash($grid);
            $check = FALSE;
            if (in_array($this->_hash, $GLOBALS['uhash']))
				$check = TRUE;
			if (strcmp($this->_parentHash, $hash) !== 0 && $check == FALSE)
				$moves[] = new Node($GLOBALS['idc']++, $this->_id, $hash, $GLOBALS['size'], $this->_dist + 1, $this->_hash);
		}
		return($moves);
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
		$this->_hash = $this->makeHash($this->_grid);
	}

	private function makeHash($grid)
	{
		foreach ($grid as $row)
			$prehash[] = implode(" ", $row);
		$hash = implode(",", $prehash);
		return($hash);
	}
}


?>
