USE [master]
GO
/****** Object:  Database [HumanResources_Proj2]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE DATABASE [HumanResources_Proj2]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'HumanResources_Proj2', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.INFO5052\MSSQL\DATA\HumanResources_Proj2.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'HumanResources_Proj2_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.INFO5052\MSSQL\DATA\HumanResources_Proj2_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
 WITH CATALOG_COLLATION = DATABASE_DEFAULT
GO
ALTER DATABASE [HumanResources_Proj2] SET COMPATIBILITY_LEVEL = 150
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [HumanResources_Proj2].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [HumanResources_Proj2] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET ARITHABORT OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [HumanResources_Proj2] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [HumanResources_Proj2] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET  ENABLE_BROKER 
GO
ALTER DATABASE [HumanResources_Proj2] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [HumanResources_Proj2] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET RECOVERY FULL 
GO
ALTER DATABASE [HumanResources_Proj2] SET  MULTI_USER 
GO
ALTER DATABASE [HumanResources_Proj2] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [HumanResources_Proj2] SET DB_CHAINING OFF 
GO
ALTER DATABASE [HumanResources_Proj2] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [HumanResources_Proj2] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [HumanResources_Proj2] SET DELAYED_DURABILITY = DISABLED 
GO
ALTER DATABASE [HumanResources_Proj2] SET ACCELERATED_DATABASE_RECOVERY = OFF  
GO
EXEC sys.sp_db_vardecimal_storage_format N'HumanResources_Proj2', N'ON'
GO
ALTER DATABASE [HumanResources_Proj2] SET QUERY_STORE = OFF
GO
USE [HumanResources_Proj2]
GO
/****** Object:  Table [dbo].[BenefitType]    Script Date: 2021-10-08 오전 4:59:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[BenefitType](
	[BenefitTypeID] [int] IDENTITY(1,1) NOT NULL,
	[BenefitType] [nvarchar](100) NOT NULL,
	[BenefitCompanyName] [nvarchar](100) NOT NULL,
	[PolicyNumber] [int] NULL,
 CONSTRAINT [PK_BenefitType] PRIMARY KEY CLUSTERED 
(
	[BenefitTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [UQ_PolicyNumber] UNIQUE NONCLUSTERED 
(
	[PolicyNumber] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Claims]    Script Date: 2021-10-08 오전 4:59:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Claims](
	[ClaimsID] [int] IDENTITY(1,1) NOT NULL,
	[ProviderID] [int] NOT NULL,
	[ClaimAmount] [decimal](18, 2) NOT NULL,
	[ServiceDate] [date] NOT NULL,
	[EmployeeBenefitID] [int] NULL,
	[ClaimDate] [date] NOT NULL,
 CONSTRAINT [PK_Claims] PRIMARY KEY CLUSTERED 
(
	[ClaimsID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Departments]    Script Date: 2021-10-08 오전 4:59:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Departments](
	[DepartmentID] [int] IDENTITY(1,1) NOT NULL,
	[DepartmentName] [nvarchar](150) NOT NULL,
	[StreetAddress] [nvarchar](100) NOT NULL,
	[City] [nvarchar](60) NOT NULL,
	[Province] [nvarchar](50) NOT NULL,
	[PostalCode] [char](6) NOT NULL,
	[MaxWorkstations] [int] NOT NULL,
 CONSTRAINT [PK_Department] PRIMARY KEY CLUSTERED 
(
	[DepartmentID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[EmployeeBenefits]    Script Date: 2021-10-08 오전 4:59:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[EmployeeBenefits](
	[EmployeeBenefitID] [int] IDENTITY(1,1) NOT NULL,
	[EmployeeId] [int] NOT NULL,
	[BenefitTypeID] [int] NOT NULL,
	[StartDate] [date] NULL,
 CONSTRAINT [PK_EmployeeBenefits] PRIMARY KEY CLUSTERED 
(
	[EmployeeBenefitID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[EmployeePhoneNumbers]    Script Date: 2021-10-08 오전 4:59:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[EmployeePhoneNumbers](
	[EmployeePhoneNumberID] [int] IDENTITY(1,1) NOT NULL,
	[EmployeeID] [int] NOT NULL,
	[PhoneTypeID] [int] NOT NULL,
	[PhoneNumber] [nvarchar](14) NULL,
 CONSTRAINT [PK_EmployeePhoneNumbers] PRIMARY KEY CLUSTERED 
(
	[EmployeePhoneNumberID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Employees]    Script Date: 2021-10-08 오전 4:59:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Employees](
	[EmployeeID] [int] IDENTITY(1,1) NOT NULL,
	[FirstName] [nvarchar](50) NOT NULL,
	[MiddleName] [nvarchar](50) NULL,
	[LastName] [nvarchar](50) NOT NULL,
	[DateofBirth] [date] NOT NULL,
	[SIN] [char](9) NOT NULL,
	[DefaultDepartmentID] [int] NULL,
	[CurrentDepartmentID] [int] NOT NULL,
	[ReportsToEmployeeID] [int] NULL,
	[StreetAddress] [nvarchar](100) NULL,
	[City] [nvarchar](60) NULL,
	[Province] [nvarchar](50) NULL,
	[PostalCode] [char](6) NULL,
	[StartDate] [date] NOT NULL,
	[BaseSalary] [decimal](18, 2) NOT NULL,
 CONSTRAINT [PK_Employee] PRIMARY KEY CLUSTERED 
(
	[EmployeeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [UQ_Employees_SIN] UNIQUE NONCLUSTERED 
(
	[SIN] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [UQ_SIN] UNIQUE NONCLUSTERED 
(
	[SIN] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[PhoneTypes]    Script Date: 2021-10-08 오전 4:59:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PhoneTypes](
	[PhoneTypeID] [int] IDENTITY(1,1) NOT NULL,
	[PhoneType] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_PhoneTypes] PRIMARY KEY CLUSTERED 
(
	[PhoneTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Providers]    Script Date: 2021-10-08 오전 4:59:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Providers](
	[ProviderID] [int] IDENTITY(1,1) NOT NULL,
	[ProviderName] [nvarchar](50) NOT NULL,
	[ProviderAddress] [nvarchar](60) NOT NULL,
	[ProviderCity] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_Providers] PRIMARY KEY CLUSTERED 
(
	[ProviderID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Index [IX_BenefitType_PolicyNumber]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_BenefitType_PolicyNumber] ON [dbo].[BenefitType]
(
	[PolicyNumber] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_Claims_FK_EmployeeBenefitID]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_Claims_FK_EmployeeBenefitID] ON [dbo].[Claims]
(
	[EmployeeBenefitID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_Claims_FK_ProviderID]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_Claims_FK_ProviderID] ON [dbo].[Claims]
(
	[ProviderID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_Claims_ProviderID_EmployeeBenefitID]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_Claims_ProviderID_EmployeeBenefitID] ON [dbo].[Claims]
(
	[ProviderID] ASC,
	[EmployeeBenefitID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeeBenefits_BenefitTypeID]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_EmployeeBenefits_BenefitTypeID] ON [dbo].[EmployeeBenefits]
(
	[BenefitTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeeBenefits_EmployeeID]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_EmployeeBenefits_EmployeeID] ON [dbo].[EmployeeBenefits]
(
	[EmployeeId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeeBenefits_EmployeeId_BenefitTypeID]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_EmployeeBenefits_EmployeeId_BenefitTypeID] ON [dbo].[EmployeeBenefits]
(
	[EmployeeId] ASC,
	[BenefitTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeePhoneNumbers_EmployeeID]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_EmployeePhoneNumbers_EmployeeID] ON [dbo].[EmployeePhoneNumbers]
(
	[EmployeeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeePhoneNumbers_EmployeeID_PhoneTypeID]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_EmployeePhoneNumbers_EmployeeID_PhoneTypeID] ON [dbo].[EmployeePhoneNumbers]
(
	[EmployeeID] ASC,
	[PhoneTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeePhoneNumbers_PhoneTypeID]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_EmployeePhoneNumbers_PhoneTypeID] ON [dbo].[EmployeePhoneNumbers]
(
	[PhoneTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [IX_Employees_]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_Employees_] ON [dbo].[Employees]
(
	[LastName] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [IX_Employees_LastName]    Script Date: 2021-10-08 오전 4:59:17 ******/
CREATE NONCLUSTERED INDEX [IX_Employees_LastName] ON [dbo].[Employees]
(
	[LastName] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Claims] ADD  CONSTRAINT [AK_DefaultClaimAmount]  DEFAULT ((0)) FOR [ClaimAmount]
GO
ALTER TABLE [dbo].[Claims] ADD  CONSTRAINT [AK_DefaultServiceDate]  DEFAULT (getdate()) FOR [ServiceDate]
GO
ALTER TABLE [dbo].[Claims] ADD  CONSTRAINT [AK_DefaultClaimDate]  DEFAULT (getdate()) FOR [ClaimDate]
GO
ALTER TABLE [dbo].[Claims]  WITH CHECK ADD  CONSTRAINT [FK_Claims_EmployeeBenefits] FOREIGN KEY([EmployeeBenefitID])
REFERENCES [dbo].[EmployeeBenefits] ([EmployeeBenefitID])
GO
ALTER TABLE [dbo].[Claims] CHECK CONSTRAINT [FK_Claims_EmployeeBenefits]
GO
ALTER TABLE [dbo].[Claims]  WITH CHECK ADD  CONSTRAINT [FK_Provider] FOREIGN KEY([ProviderID])
REFERENCES [dbo].[Providers] ([ProviderID])
GO
ALTER TABLE [dbo].[Claims] CHECK CONSTRAINT [FK_Provider]
GO
ALTER TABLE [dbo].[EmployeeBenefits]  WITH CHECK ADD  CONSTRAINT [FK_BenefitType] FOREIGN KEY([BenefitTypeID])
REFERENCES [dbo].[BenefitType] ([BenefitTypeID])
GO
ALTER TABLE [dbo].[EmployeeBenefits] CHECK CONSTRAINT [FK_BenefitType]
GO
ALTER TABLE [dbo].[EmployeeBenefits]  WITH CHECK ADD  CONSTRAINT [FK_Employee] FOREIGN KEY([EmployeeId])
REFERENCES [dbo].[Employees] ([EmployeeID])
GO
ALTER TABLE [dbo].[EmployeeBenefits] CHECK CONSTRAINT [FK_Employee]
GO
ALTER TABLE [dbo].[EmployeePhoneNumbers]  WITH CHECK ADD  CONSTRAINT [FK_EmployeePhoneNumbers_Employee] FOREIGN KEY([EmployeeID])
REFERENCES [dbo].[Employees] ([EmployeeID])
GO
ALTER TABLE [dbo].[EmployeePhoneNumbers] CHECK CONSTRAINT [FK_EmployeePhoneNumbers_Employee]
GO
ALTER TABLE [dbo].[EmployeePhoneNumbers]  WITH CHECK ADD  CONSTRAINT [FK_EmployeePhoneNumbers_PhoneTypes] FOREIGN KEY([PhoneTypeID])
REFERENCES [dbo].[PhoneTypes] ([PhoneTypeID])
GO
ALTER TABLE [dbo].[EmployeePhoneNumbers] CHECK CONSTRAINT [FK_EmployeePhoneNumbers_PhoneTypes]
GO
ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [FK_Employee_Department_Current] FOREIGN KEY([CurrentDepartmentID])
REFERENCES [dbo].[Departments] ([DepartmentID])
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [FK_Employee_Department_Current]
GO
ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [FK_Employee_Department_Default] FOREIGN KEY([DefaultDepartmentID])
REFERENCES [dbo].[Departments] ([DepartmentID])
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [FK_Employee_Department_Default]
GO
ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [FK_Employee_ReportsTo] FOREIGN KEY([ReportsToEmployeeID])
REFERENCES [dbo].[Employees] ([EmployeeID])
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [FK_Employee_ReportsTo]
GO
ALTER TABLE [dbo].[Claims]  WITH CHECK ADD  CONSTRAINT [AK_Claims_CheckClaimDate] CHECK  (([ClaimDate]>=getdate()))
GO
ALTER TABLE [dbo].[Claims] CHECK CONSTRAINT [AK_Claims_CheckClaimDate]
GO
ALTER TABLE [dbo].[Claims]  WITH CHECK ADD  CONSTRAINT [AK_Claims_CheckServiceDate] CHECK  (([ServiceDate]>=getdate()))
GO
ALTER TABLE [dbo].[Claims] CHECK CONSTRAINT [AK_Claims_CheckServiceDate]
GO
ALTER TABLE [dbo].[Departments]  WITH CHECK ADD  CONSTRAINT [AK_CheckMax] CHECK  (([MaxWorkstations]>(0)))
GO
ALTER TABLE [dbo].[Departments] CHECK CONSTRAINT [AK_CheckMax]
GO
ALTER TABLE [dbo].[EmployeeBenefits]  WITH CHECK ADD  CONSTRAINT [AK_EmployeeBenefits_CheckStartDate] CHECK  (([StartDate]>=getdate()))
GO
ALTER TABLE [dbo].[EmployeeBenefits] CHECK CONSTRAINT [AK_EmployeeBenefits_CheckStartDate]
GO
USE [master]
GO
ALTER DATABASE [HumanResources_Proj2] SET  READ_WRITE 
GO
