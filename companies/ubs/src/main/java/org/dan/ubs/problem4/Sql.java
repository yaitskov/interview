package org.dan.ubs.problem4;

public class Sql {
    String query = "select Tenants.TenantName, count(AptTenants.AptID) "
            + " from Tenants inner join AptTenants"
            + " on (Tenants.TenantId = AptTenants.TenantID)"
            + " group by Tenants.TenantName"
            + " having count(AptTenants.AptID) > 1"
            + " order by Tenants.TenantName";
}
