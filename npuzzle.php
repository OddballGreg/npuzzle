<?php

/*php error reporting code, remove before submission                               */
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

require_once("parse.php");
require_once("Node.class.php");
require_once("heuristics.php");
require_once("solve.php");

const HAMMING = 1;
const MANHATTAN = 2;
const EUCLIDEAN = 3;

$GLOBALS['sol'] = NULL; // Solution
$GLOBALS['osets'] = array(); // Open Sets
$GLOBALS['csets'] = array(); // Closed Sets
$GLOBALS['idc'] = 0; // ID counter
$GLOBALS['size'] = 3; // Grid Size

if (isset($argv[1]) && file_exists($argv[1]) == TRUE)
	$GLOBALS['osets'][] = new Node($GLOBALS['idc']++, "Initial", parse($argv[1]), $GLOBALS['size'], 0, NULL);
else
{
	echo "Invalid file or no puzzle given, automatically generating random 3x3 puzzle\n";
	$GLOBALS['osets'][] = new Node($GLOBALS['idc']++, "Initial", genPuzzle(), $GLOBALS['size'], 0, NULL); //genPuzzle() is undefined currently
}
$GLOBALS['sol'] = new Node("sol", "Solution", $GLOBALS['osets'][0]->getHash(), $GLOBALS['size'], 0, NULL);
$GLOBALS['sol']->setGoal();
$GLOBALS['hstc'] = HAMMING;

echo "\nPlease select the heuristic you would like to use to solve this puzzle...";
echo "\n(1) Hamming Distance Heuristic\n(2) Manhattan Distance Heuristic\n(3) Euclidean Distance Heuristic\n";
		userin:
$line = fgets(STDIN);
if (strncmp($line, '1', 1) == 0)
	$GLOBALS['hstc'] = HAMMING;
else if (strncmp($line, '2', 1) == 0)
	$GLOBALS['hstc'] = MANHATTAN;
else if (strncmp($line, '3', 1) == 0)
	$GLOBALS['hstc'] = EUCLIDEAN;
else
{
	echo "Please enter either 1, 2, or 3\n";
	goto userin;
}

$GLOBALS['osets'][0]->setCost();
$GLOBALS['sol']->setCost(0);
echo "\n" . $GLOBALS['osets'][0] . "\n";
echo $GLOBALS['sol'] . "\n\n";

solve();

?>
