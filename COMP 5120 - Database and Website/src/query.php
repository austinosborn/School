<html>
<head>
    <title>
      AEO0015db Query Results
    </title>
</head>
</html>
<?php
//Get input from index.php
$query = $_POST['queryBox'];
$query = stripslashes($query);
$queryLower = strtolower($query);
//IF IT CONTAINS DROP, KILL IT WITH FIRE!
if (strpos($queryLower, 'drop') !== false) {
  exit("Drop operation not allowed in query");
}

$servername = "mysql.auburn.edu";
$username = "aeo0015";
$password = "!Rock333";
$dbname = "aeo0015db";

echo "<h3>Results of your query:</h3>";
$conn = mysqli_connect($servername, $username, $password, $dbname);
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
$result = mysqli_query($conn, $query) or die(mysqli_error($conn));
if (mysqli_num_rows($result) > 0) {
  //Print table headers
  $finfo = $result->fetch_fields();
  echo "<table><tr>";
  foreach ($finfo as $val) {
    // code...
    echo ("<th>$val->name</th>");
  }
  echo "</tr>";
  //For each row
  while($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        //For each item in row
        foreach ($row as $item) {
          echo "<td>";
          echo $item;
          echo "</td>";
        }
        echo "</tr>";
    }
} else {
    echo "0 results";
}
echo "</table>";
echo "<br>";
 ?>
