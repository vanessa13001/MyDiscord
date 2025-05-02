#include <stdio.h>
#include "role.h"

// function to display user permissions
void displayPermissions(UserPermissions permissions) {
    printf("Role: %d\n", permissions.role);
    printf("Can Create Channel: %s\n", permissions.canCreateChannel ? "Yes" : "No");
    printf("Can Delete Channel: %s\n", permissions.canDeleteChannel ? "Yes" : "No");
    printf("Can Ban User: %s\n", permissions.canBanUser ? "Yes" : "No");
    printf("Can Assign Roles: %s\n", permissions.canAssignRoles ? "Yes" : "No");
}

int main() {
    Role userRole = ADMINISTRATOR; 
    Role targetUserRole = MEMBER; 
    Role newRole = MODERATOR; 

    // Get permissions based on the user's role
    UserPermissions permissions = getPermissions(userRole);

    // Display permissions
    printf("Permissions for current user (ADMINISTRATOR):\n");
    displayPermissions(permissions);

    // actions based on the role
    printf("\nTesting actions for ADMINISTRATOR:\n");
    createChannel(userRole);
    deleteChannel(userRole);
    banUser(userRole);

    // assigning roles  
    printf("\nAssigning role MODERATOR to a MEMBER:\n");
    assignRole(userRole, targetUserRole, newRole);

    // assigning ADMINISTRATOR role (should fail)
    printf("\nAttempting to assign role ADMINISTRATOR to a MEMBER:\n");
    assignRole(userRole, targetUserRole, ADMINISTRATOR);

    // role assignment by a MEMBER (should fail)
    printf("\nAttempting to assign role MODERATOR to a MEMBER by another MEMBER:\n");
    assignRole(MEMBER, targetUserRole, MODERATOR);

    return 0;
}
