package com.shumin.app;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

/**
 * Unit test for Employee allocation fee applications. 
 */
public class EmployeeTest extends TestCase
{
    private double epsilon = 0.00001;

    public EmployeeTest( String testName ) {
        super( testName );
    }

    public static Test suite() {
        return new TestSuite( EmployeeTest.class );
    }

    public void testEmployee() {
        QATester tester = new QATester(); 
        Developer developer1 = new Developer(); 
        Developer developer2 = new Developer();
        Manager managerB = new Manager(); 
        Manager managerA = new Manager(); 
        managerB.addEmployee(tester); 
        managerB.addEmployee(developer1); 
        managerB.addEmployee(developer2); 
        managerA.addEmployee(managerB);
        managerA.addEmployee(managerB);

        assertEquals(1000, developer2.getFee(), epsilon); 
        assertEquals(2800, managerB.getFee(), epsilon); 
        assertEquals(3100.0, managerA.getFee(), epsilon); 
    }

    public void testABC() {
        QATester tester = new QATester();
        assertEquals(500, tester.getFee(), epsilon); 
    }
}
