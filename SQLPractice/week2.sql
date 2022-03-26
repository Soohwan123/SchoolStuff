
USE TestDB
GO

CREATE TABLE dbo.OrderValues (
    CustomerID  INT,
    OrderID     INT,
    TotalValue  MONEY,
    EnteredDate DATETIME,
    ChangedDate DATETIME );


INSERT INTO dbo.OrderValues (
		 CustomerID,
	OrderID,
	TotalValue,
      EnteredDate )
SELECT o.CustomerID,
       o.OrderID, 
	   SUM(ol.UnitPrice * ol.Quantity) AS TotalValue,
	 GETDATE() AS EnteredDate
FROM WideWorldImporters.Sales.Orders o
INNER JOIN WideWorldImporters.Sales.OrderLines ol
	ON o.OrderID = ol.OrderID
WHERE o.CustomerID IN ( 801, 802 )
GROUP BY o.OrderID, o.CustomerID;
GO

TRUNCATE TABLE dbo.OrderValues;
GO


SELECT *
FROM dbo.OrderValues
WHERE CustomerID = (SELECT * FROM WideWorldImporters.Sales.Customers WHERE CustomerName = 'Cosmina Vlad')


UPDATE ov
SET ov.TotalValue = ov.TotalValue + 10,
    ov.ChangedDate = GETDATE()
FROM dbo.OrderValues ov
INNER JOIN WideWorldImporters.Sales.Customers cu
	ON ov.CustomerID = cu.CustomerID
WHERE cu.CustomerName = 'Cosmina Vlad';

DELETE ov
FROM dbo.OrderValues ov
INNER JOIN WideWorldImporters.Sales.Customers cu
    ON ov.CustomerID = cu.CustomerID
WHERE cu.CustomerName = 'Cosmina Vlad';




UPDATE ov
SET ov.ChangedDate = GETDATE()
OUTPUT inserted.EnteredDate,
       deleted.ChangedDate AS OldDate,
       inserted.ChangedDate AS NewDate
FROM dbo.OrderValues ov
INNER JOIN WideWorldImporters.Sales.Customers cu
	ON ov.CustomerID = cu.CustomerID
WHERE cu.CustomerName = 'Cosmina Vlad';


SELECT *
FROM WideWorldImporters.Sales.Customers
WHERE CustomerName LIKE 'Co_m%'

SELECT *
FROM WideWorldImporters.Sales.Customers
WHERE CustomerID IN (801, 802)


SELECT *
FROM dbo.OrderValues
WHERE CustomerID IN (SELECT CustomerID FROM WideWorldImporters.Sales.Customers WHERE CustomerName LIKE 'C%')


USE WideWorldImporters;
GO

SELECT o.*
FROM Sales.Orders o
WHERE EXISTS ( SELECT 1
               FROM Sales.Customers cu
               WHERE cu.CustomerName = 'Cosmina Vlad'
                     AND o.CustomerID = cu.CustomerID );