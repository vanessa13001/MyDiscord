#ifndef ROLE_H
#define ROLE_H

// Definition of roles
typedef enum {
    MEMBER,
    MODERATOR,
    ADMINISTRATOR
} Role;

// Structure to store user permissions
typedef struct {
    Role role;
    int canCreateChannel;
    int canDeleteChannel;
    int canBanUser;
    int canAssignRoles;
} UserPermissions;

// Function prototypes
UserPermissions getPermissions(Role role);
void createChannel(Role role);
void deleteChannel(Role role);
void banUser(Role role);
void assignRole(Role currentRole, Role targetRole, Role newRole);

#endif // ROLE_H
