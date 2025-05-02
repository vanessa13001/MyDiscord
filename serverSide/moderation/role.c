#include <stdio.h>
#include "role.h"

// function to display user permissions
UserPermissions getPermissions(Role role) {
    UserPermissions permissions;
    permissions.role = role;

    //initialization of permissions based on the role
    switch (role) {
        case MEMBER:
            permissions.canCreateChannel = 0;
            permissions.canDeleteChannel = 0;
            permissions.canBanUser = 0;
            permissions.canAssignRoles = 0;
            break;
        case MODERATOR:
            permissions.canCreateChannel = 1;
            permissions.canDeleteChannel = 1;
            permissions.canBanUser = 1;
            permissions.canAssignRoles = 0;
            break;
        case ADMINISTRATOR:
            permissions.canCreateChannel = 1;
            permissions.canDeleteChannel = 1;
            permissions.canBanUser = 1;
            permissions.canAssignRoles = 1;
            break;
        default:
            permissions.canCreateChannel = 0;
            permissions.canDeleteChannel = 0;
            permissions.canBanUser = 0;
            permissions.canAssignRoles = 0;
            break;
    }

    return permissions;
}

// function to create a channel
void createChannel(Role role) {
    UserPermissions permissions = getPermissions(role);
    if (permissions.canCreateChannel) {
        printf("Channel created successfully.\n");
    } else {
        printf("You do not have permission to create a channel.\n");
    }
}

// Fonction pour supprimer un canal
void deleteChannel(Role role) {
    UserPermissions permissions = getPermissions(role);
    if (permissions.canDeleteChannel) {
        printf("Channel deleted successfully.\n");
    } else {
        printf("You do not have permission to delete a channel.\n");
    }
}

// function to ban a user   
void banUser(Role role) {
    UserPermissions permissions = getPermissions(role);
    if (permissions.canBanUser) {
        printf("User banned successfully.\n");
    } else {
        printf("You do not have permission to ban a user.\n");
    }
}

// function to assign a role to a user     
void assignRole(Role currentRole, Role targetRole, Role newRole) {
    UserPermissions permissions = getPermissions(currentRole);
    if (permissions.canAssignRoles) {

        // Check that the target role is not ADMINISTRATOR
        if (newRole == ADMINISTRATOR) {
            printf("Cannot assign ADMINISTRATOR role.\n");
        } else {
            printf("Role assigned successfully. User is now a %s.\n", newRole == MEMBER ? "MEMBER" : "MODERATOR");
        }
    } else {
        printf("You do not have permission to assign roles.\n");
    }
}
