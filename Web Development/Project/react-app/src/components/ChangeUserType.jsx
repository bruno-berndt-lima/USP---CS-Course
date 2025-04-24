import './ChangeUserType.css'

const ChangeUserType = ({ user, isAdmin, onUserTypeChange }) => {
  const updateUserType = async () => {
    try {
      const updatedUser = {
        ...user,
        admin: !isAdmin,
      };

      const response = await fetch(`http://localhost:7000/users/${user._id}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(updatedUser),
      });

      if (response.ok) {
        onUserTypeChange(!isAdmin);
        console.log('User type updated successfully');
      } else {
        console.log('User type update failed');
      }
    } catch (error) {
      console.error('Error updating user type:', error);
    }
  };

  return (
    <>
    <div className="change-user-type">
      {isAdmin ? (
        <button  onClick={updateUserType}>Change to Normal User</button>
        ) : (
          <button onClick={updateUserType}>Change to Admin</button>
          )}
    </div>
    </>
  );
};

export default ChangeUserType;
