import React from 'react'


export const MessageItem = React.memo<{message: string, type: 'sent' | 'received'}>(({ message, type }) => (
    <div 
      className={`
        p-2 rounded-lg max-w-[80%] my-1 
        ${type === 'sent' 
          ? 'bg-blue-700 text-white self-end ml-auto' 
          : 'bg-green-700 text-white self-start mr-auto'}
      `}
    >
      {message}
    </div>
  ));