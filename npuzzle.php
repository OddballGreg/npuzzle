<?php

/*php error reporting code, remove before submission                               */
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

require_once("parse.php");

if ($argc < 2)
	die("Too few arguements given\n");
if (file_exists($argv[1]) == FALSE)
	die("File does not exit\n");

$GLOBALS['solution'] = NULL;
$GLOBALS['opensets'] = NULL;
$GLOBALS['closedsets'] = NULL;

print(parse($argv[1]));

echo "\nPlease select the heuristic you would like to use to solve this puzzle...";
echo "\n(1) Manhattan Distance Heuristic\n(2) Hamming Distance Heuristic\n(3) Euclidean Distance Heuristic\n";
		userin:
$line = fgets(STDIN);
if (strncmp($line, '1', 1) == 0)
	;
else if (strncmp($line, '2', 1) == 0)
	;
else if (strncmp($line, '3', 1) == 0)
	;
else
{
	echo "Please enter either 1, 2, or 3\n";
	goto userin;
}

?>