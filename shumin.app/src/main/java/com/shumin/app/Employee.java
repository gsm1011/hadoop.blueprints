package com.shumin.app; 

abstract class Employee {
    protected double fee; 
    Employee(double f) { fee = f; } 
    public double getFee() {
        return fee; 
    } 
}
