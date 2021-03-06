--/*
USE MASTER;
GO

DROP DATABASE IF EXISTS HumanResources_Proj2;
GO
--*/

CREATE DATABASE HumanResources_Proj2;
GO

USE HumanResources_Proj2
GO

CREATE TABLE dbo.Departments(
	DepartmentID INT IDENTITY(1,1) CONSTRAINT PK_Department PRIMARY KEY,
	DepartmentName NVARCHAR(150) NOT NULL,
	StreetAddress NVARCHAR(100) NOT NULL,
	City NVARCHAR(60) NOT NULL,
	Province NVARCHAR(50) NOT NULL,
	PostalCode CHAR(6) NOT NULL,
	MaxWorkstations INT NOT NULL
);

CREATE TABLE dbo.PhoneTypes(
	PhoneTypeID INT IDENTITY(1,1) CONSTRAINT PK_PhoneTypes PRIMARY KEY,
	PhoneType NVARCHAR(50) NOT NULL,
);
  
CREATE TABLE dbo.Employees(
	EmployeeID INT IDENTITY(1,1) CONSTRAINT PK_Employee PRIMARY KEY,
	FirstName NVARCHAR(50) NOT NULL,
	MiddleName NVARCHAR(50) NULL,
	LastName NVARCHAR(50) NOT NULL,
	DateofBirth DATE NOT NULL,
	SIN char(9) NOT NULL,
	DefaultDepartmentID  INT NOT NULL CONSTRAINT FK_Employee_Department_Default REFERENCES dbo.Departments ( DepartmentID ),
    CurrentDepartmentID  INT NOT NULL CONSTRAINT FK_Employee_Department_Current REFERENCES dbo.Departments ( DepartmentID ),
	ReportsToEmployeeID INT NULL CONSTRAINT FK_Employee_ReportsTo REFERENCES dbo.Employees ( EmployeeID ),
	StreetAddress NVARCHAR(100) NULL,
	City NVARCHAR(60) NULL,
	Province NVARCHAR(50) NULL,
	PostalCode CHAR(6) NULL,
	StartDate  DATE NOT NULL,
	BaseSalary decimal(18, 2) NOT NULL,
-- 	BonusPercent decimal(3, 2) NOT NULL -- Best not to Store, as this Can be calculated from Employee data
);

CREATE TABLE dbo.EmployeePhoneNumbers(
	EmployeePhoneNumberID INT IDENTITY CONSTRAINT PK_EmployeePhoneNumbers PRIMARY KEY,
	EmployeeID INT NOT NULL CONSTRAINT FK_EmployeePhoneNumbers_Employee REFERENCES dbo.Employees ( EmployeeID ),
	PhoneTypeID INT NOT NULL CONSTRAINT FK_EmployeePhoneNumbers_PhoneTypes REFERENCES dbo.PhoneTypes (PhoneTypeID ),
	PhoneNumber NVARCHAR(14) NULL
); 

CREATE TABLE dbo.BenefitType(
	BenefitTypeID INT IDENTITY CONSTRAINT PK_BenefitType PRIMARY KEY, 
	BenefitType NVARCHAR(100) NOT NULL,
	BenefitCompanyName NVARCHAR(100) NOT NULL,
        PolicyNumber INT NULL
);

CREATE TABLE dbo.EmployeeBenefits(
	EmployeeBenefitID INT IDENTITY CONSTRAINT PK_EmployeeBenefits PRIMARY KEY, 
	EmployeeId INT NOT NULL CONSTRAINT FK_Employee REFERENCES dbo.Employees ( EmployeeID ),
	BenefitTypeID INT NOT NULL CONSTRAINT FK_BenefitType REFERENCES dbo.BenefitType ( BenefitTypeID  ),
    StartDate DATE NULL,
	CONSTRAINT EmployeeBenefits_StartDate_Check CHECK (StartDate <= GETDATE()),
	CONSTRAINT EmployeeBenefits_StartDate_Default DEFAULT (GETDATE())

);

CREATE TABLE dbo.Providers (
	ProviderID INT IDENTITY CONSTRAINT PK_Providers PRIMARY KEY, 
	ProviderName  NVARCHAR(50) NOT NULL,
	ProviderAddress NVARCHAR(60) NOT NULL,
	ProviderCity NVARCHAR(50) NOT NULL,
);

CREATE TABLE dbo.Claims(
	ClaimsID INT IDENTITY CONSTRAINT PK_Claims PRIMARY KEY, 
	ProviderID INT NOT NULL CONSTRAINT FK_Provider REFERENCES dbo.Providers ( ProviderID ),
	ClaimAmount decimal(18, 2) NOT NULL,
	ServiceDate DATE NOT NULL,
	EmployeeBenefitID INT NULL CONSTRAINT FK_Claims_EmployeeBenefits REFERENCES dbo.EmployeeBenefits ( EmployeeBenefitID ),
	ClaimDate DATE NOT NULL,
);

GO

ALTER TABLE Employees ADD CONSTRAINT UQ_Employees_SIN UNIQUE(SIN);
GO

ALTER TABLE [dbo].[Departments] ADD CONSTRAINT AK_CheckMax CHECK([MaxWorkstations] > 0);

ALTER TABLE [dbo].[Departments] ADD CONSTRAINT UQ_DepartmentName UNIQUE(DepartmentName);

CREATE INDEX IX_Departments_DepartmentName ON  [dbo].[Departments] (DepartmentName);

ALTER TABLE  [dbo].[Employees] ADD CONSTRAINT AK_Employees_CheckDateOfBirth CHECK([DateofBirth] >= GETDATE());
ALTER TABLE  [dbo].[Employees] ADD CONSTRAINT AK_Employees_CheckStartDate CHECK([StartDate] >= GETDATE());
ALTER TABLE  [dbo].[EmployeeBenefits] ADD CONSTRAINT AK_EmployeeBenefits_CheckStartDate CHECK([StartDate] >= GETDATE());
ALTER TABLE  [dbo].[Claims] ADD CONSTRAINT AK_Claims_CheckServiceDate CHECK([ServiceDate] >= GETDATE());
ALTER TABLE  [dbo].[Claims] ADD CONSTRAINT AK_Claims_CheckClaimDate CHECK([ClaimDate] >= GETDATE());

ALTER TABLE  [dbo].[BenefitType] ADD CONSTRAINT UQ_PolicyNumber UNIQUE(PolicyNumber);
CREATE INDEX IX_BenefitType_PolicyNumber ON [dbo].[BenefitType] (PolicyNumber);

ALTER TABLE [dbo].[Employees] ADD CONSTRAINT AK_DefaultBaseSalary DEFAULT 0 For BaseSalary;
ALTER TABLE Claims ADD CONSTRAINT AK_DefaultClaimAmount DEFAULT 0 For ClaimAmount;
ALTER TABLE Departments ADD CONSTRAINT AK_DefaultMaxWorkStations DEFAULT 1 For MaxWorkStations;
ALTER TABLE Claims ADD CONSTRAINT AK_DefaultClaimDate DEFAULT GETDATE() For ClaimDate;
ALTER TABLE Claims ADD CONSTRAINT AK_DefaultServiceDate DEFAULT GETDATE() For ServiceDate;


CREATE INDEX IX_Employees_Cities_PostalCode ON Employees(City, PostalCode);
CREATE INDEX IX_Employees_Cities ON Employees(City);
CREATE INDEX IX_Employees_PostalCode ON Employees(PostalCode);

CREATE INDEX IX_Claims_FK_EmployeeBenefitID ON Claims([EmployeeBenefitID]);
CREATE INDEX IX_Claims_FK_ProviderID ON Claims([ProviderID]);

CREATE INDEX IX_EmployeeBenefits_BenefitTypeID ON EmployeeBenefits(BenefitTypeID);
CREATE INDEX IX_EmployeeBenefits_EmployeeID ON EmployeeBenefits(EmployeeID);

CREATE INDEX IX_EmployeePhoneNumbers_EmployeeID ON EmployeePhoneNumbers(EmployeeID);
CREATE INDEX IX_EmployeePhoneNumbers_PhoneTypeID ON EmployeePhoneNumbers(PhoneTypeID);

CREATE INDEX IX_Employees_DefaultDepartmentID ON Employees([DefaultDepartmentID]);
CREATE INDEX IX_Employees_CurrentDepartmentID ON Employees([CurrentDepartmentID]);
CREATE INDEX IX_Employees_ReportsToEmployeeID ON Employees([ReportsToEmployeeID]);

CREATE INDEX IX_Claims_ProviderID_EmployeeBenefitID ON Claims(ProviderID, EmployeeBenefitID);
CREATE INDEX IX_EmployeeBenefits_EmployeeId_BenefitTypeID ON EmployeeBenefits(EmployeeId, BenefitTypeID);
CREATE INDEX IX_EmployeePhoneNumbers_EmployeeID_PhoneTypeID ON EmployeePhoneNumbers(EmployeeID, PhoneTypeID);
GO

--CREATE INDEX IX_Employees_LastName ON HumanResources_Proj2.dbo.Employees (LastName);
--GO
--DROP INDEX IX_Employees_ ON Employees;
--DROP INDEX IX_Employees_LastName ON Employees;


--CREATE INDEX FK_EmployeeBenefits_EmployeeId ON EmployeeBenefits (EmployeeId, BenefitTypeID); /*sorting parameter BenefitTypeID -> improving performance */
--GO
--DROP INDEX FK_EmployeeBenefits_EmployeeId On EmployeeBenefits;
--GO
/*Two way optimazation */


--CREATE INDEX IX_EmployeePhoneNumbers_PhoneTypeID_EmployeeID ON EmployeePhoneNumbers
--(PhoneTypeID, EmployeeID);
--GO   





--UQ_TableName_ColumnName

SELECT FirstName FROM EmployeePhoneNumbers INNER JOIN Employees ON WHERE PhoneTypeID = 1

SELECT FirstName FROM EmployeePhoneNumbers INNER JOIN Employees ON WHERE EmployeeID = 100

SELECT * FROM Departments; 
GO
