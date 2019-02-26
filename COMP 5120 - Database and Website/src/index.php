
<!DOCTYPE html>
<html>
<!-- Head -->
<head>
    <title>
      AEO0015db Website
    </title>
</head>
<!-- Body -->
<body>
  <h2> Welcome to Austin Osborn's COMP 5120 Database website </h2>
  <p> The following shows all of the relations in the Books database.<br>
  </p>

<?php
$servername = "mysql.auburn.edu";
$username = "aeo0015";
$password = "!Rock333";
$dbname = "aeo0015db";

$conn = mysqli_connect($servername, $username, $password, $dbname);
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
$titleList = Array("Books","Customers","Employees","Order_Details","Orders","Shippers","Subjects","Suppliers");
$select = "SELECT * from ";
//For each table
foreach ($titleList as $title) {
  $sql = "$select $title";
  $result = mysqli_query($conn, $sql);
  echo "<h3>$title Table</h3>";
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

}

mysqli_close($conn);
?>

<!--Text box-->
<form name ='form' method ='post' action="query.php">
Input query here:<br> <textarea type="text" name="queryBox" id = "queryBox" style="height:100px;width:500px" rows = "10" cols = "80"></textarea><br>
<input type="submit" name="submit" value="Submit">
</form>



</body>
</html>
