# Inventory Management & Package Sorting System

This project contains solutions to two problems: 
1. **Inventory Tracker in a Warehouse**
2. **Multi-Field Package Sorting System**

---

## 🚚 Question 1: Inventory Tracker in a Warehouse

You are managing inventory in a warehouse. Each item has:
- A **unique Product ID**
- A **current stock count**

You receive a batch of **sales orders**, and your system must process each one by updating the inventory.

### 📋 Initial Inventory Table:
| Product ID | Stock Count |
|------------|-------------|
| P101       | 10          |
| P102       | 5           |
| P103       | 20          |
| P104       | 0           |

### 🧾 Sales Orders Table:
| Product ID | Quantity |
|------------|----------|
| P101       | 3        |
| P103       | 7        |
| P102       | 2        |
| P104       | 4        |

### ✅ Program Requirements:
1. **Process each sales order**:  
   - Update the inventory if there is enough stock.
   - Display status: `"Order processed: <Product ID>"`

2. **Handle insufficient stock**:  
   - Skip the order.
   - Log it into a `"Failed Orders"` table with a failure reason.
   - Display status: `"Order failed: <Product ID> - Insufficient stock"`

3. **Final Output**:  
   - Display the updated inventory table.
   - Display the failed orders table.

---

## 📦 Question 2: Multi-Field Package Sorting System

Each package on the conveyor belt has the following properties:
- **Package ID** (string)
- **Priority Level** (integer) – lower number = higher priority
- **Weight** (float, in kg)

### 🧠 Objective:
You need to sort the packages with **two conditions**:
1. **Primary sort** by `Priority` (ascending)
2. **If priorities are the same**, sort by `Weight` (ascending)

### 🔽 Input Sample:

| Package ID | Priority | Weight |
|------------|----------|--------|
| PKG1       | 3        | 5.2 kg |
| PKG2       | 1        | 7.5 kg |
| PKG3       | 2        | 4.0 kg |
| PKG4       | 1        | 2.3 kg |
| PKG5       | 3        | 5.2 kg |

### 🖨 Output:
Sorted packages by:
- **Priority (ascending)**
- Then by **Weight (ascending)**

---

## 🛠 Technologies Used
- Language: C++
- File I/O: CSV files (for Question 1)
- Sorting: Custom comparator (for Question 2)

---

## 📝 Author
Developed as part of an evaluation for a **Software Intern** role at Thiran Technologies.

