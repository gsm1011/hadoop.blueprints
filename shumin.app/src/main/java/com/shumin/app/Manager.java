package com.shumin.app;

import java.util.Vector; 

class Manager extends Employee {
    Manager() { super(300); }
    
    private Vector<Employee> employees = new Vector<Employee>(); 

    public void addEmployee(Employee e) {
        if(employees.indexOf(e) < 0) {
            employees.add(e); 
        }
    }

    public void removeEmployee(Employee e) {
        employees.remove(e); 
    }

    @Override
    public double getFee() {
        double totalFee = fee; 
        for(Employee e : employees) {
            totalFee += e.getFee(); 
        }
        return totalFee;
    }
}
