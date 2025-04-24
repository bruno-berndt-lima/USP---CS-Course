import React from 'react';
import { useState, useEffect } from 'react';
import UsersDetails from './adminUsersDetails';
import './adminUsers.css'

const AdminUsers = () => {    
    const [users, setUsers] = useState([]);
    useEffect(() => {
      fetch('http://localhost:7000/users')
        .then(response => response.json())
        .then(data => setUsers(data))
        .catch(error => console.log(error));
    }, []);
    
    const handleUserDeleted = (userId) => {
        setUsers(users.filter((user) => user._id !== userId));
      };

    return (
        <div className="users-container">
            {users && users.map(user => (
                <UsersDetails user={user} key={user._id} onUserDeleted={handleUserDeleted}/>
            ))}
        </div>
    );
}
 
export default AdminUsers;