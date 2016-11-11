<?php

function solve()
{
	$GLOBALS['osets'] = array_merge($GLOBALS['osets'], $GLOBALS['osets'][0]->genMoves());
	$GLOBALS['csets'] = $GLOBALS['osets'][0];
	$GLOBALS['osets'] = array_splice($GLOBALS['osets'], 1);

}

//function 

?>