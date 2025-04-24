import { FaTrash } from 'react-icons/fa';
import './DeleteUser.css'

const DeleteUser = ({userId, onUserDeleted}) => {
    const handleDeleteUser = () => {
        const userToRemove = { id: userId };
        console.log(JSON.stringify(userToRemove));
  
        fetch(`http://localhost:7000/users`, {
            method: 'DELETE',
            headers: {
            'Content-Type': 'application/json',
            },
            body: JSON.stringify(userToRemove),
        })
            .then(() => {
                onUserDeleted();
                console.log('User deleted');
            })
            .catch(error => console.log(error));
        };
   
    return (
        <div className='delete-user-btn'>
            <button onClick={handleDeleteUser}>
                <FaTrash />
            </button> 
        </div>
    );
};

export default DeleteUser;
