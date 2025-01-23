import { useEffect, useRef, useState } from 'react';
// import { MessageItem } from './components/messageItem';

function App() {
  const [socket, setSocket] = useState<WebSocket | null>(null);
  const [currentRoom, setCurrentRoom] = useState('Enter Room ID');
  const [messages, setMessages] = useState<
    { id: number; message: string; type: 'sent' | 'received' }[]
  >([]);

  const roomIdInput = useRef<HTMLInputElement | null>(null);
  const messageInput = useRef<HTMLInputElement | null>(null);

  useEffect(() => {
    const newSocket = new WebSocket('https://chatapp-backend-deb6.onrender.com');

    newSocket.onopen = () => setSocket(newSocket);

    newSocket.onmessage = (event) => {
      const data = JSON.parse(event.data);
      if (data.type === 'chat') {
        setMessages((prev) => [
          ...prev,
          { id: Date.now(), message: data.payload.message, type: 'received' },
        ]);
      }
    };

    return () => newSocket.close();
  }, []);

  const joinRoom = (roomId: string) => {
    if (socket && roomId.trim()) {
      socket.send(
        JSON.stringify({
          type: 'join',
          payload: { roomId },
        })
      );
      setCurrentRoom(roomId);
    }
  };

  const sendMessage = (messageText: string) => {
    if (socket && messageText.trim()) {
      socket.send(
        JSON.stringify({
          type: 'chat',
          payload: { message: messageText },
        })
      );
      setMessages((prev) => [
        ...prev,
        { id: Date.now(), message: messageText, type: 'sent' },
      ]);

      if (messageInput.current) {
        messageInput.current.value = '';
      }
    }
  };

  return (
    <div className="min-h-screen bg-black flex items-center justify-center p-4">
      <div className="w-full max-w-lg border border-gray-400 rounded-lg overflow-hidden">
        {/* Room Join Section */}
        <div className="flex p-4 border-b border-gray-400">
          <input
            ref={roomIdInput}
            type="text"
            placeholder={currentRoom}
            className="flex-grow p-2 border border-gray-400 rounded-l-md bg-transparent text-white placeholder-gray-500"
          />
          <button
            onClick={() => joinRoom(roomIdInput.current?.value || '')}
            className="px-4 py-2 border border-green-500 text-green-500 rounded-r-md hover:bg-green-500 hover:text-black"
          >
            Join
          </button>
        </div>

        {/* Messages Display Section */}
        <div className="flex-grow p-4 bg-black text-white overflow-y-auto space-y-4" style={{ height: '60vh' }}>
          {messages.length === 0 ? (
            <p className="text-gray-500 text-center">No messages yet.</p>
          ) : (
            messages.map((msg) => (
              <div
                key={msg.id}
                className={`p-2 max-w-[70%] rounded-md ${
                  msg.type === 'sent' ? 'ml-auto bg-blue-500 text-white' : 'mr-auto bg-gray-700 text-white'
                }`}
              >
                {msg.message}
              </div>
            ))
          )}
        </div>

        {/* Message Input Section */}
        <div className="flex p-4 border-t border-gray-400">
          <input
            ref={messageInput}
            type="text"
            placeholder="Type a message"
            className="flex-grow p-2 border border-gray-400 rounded-l-md bg-transparent text-white placeholder-gray-500"
          />
          <button
            onClick={() => sendMessage(messageInput.current?.value || '')}
            className="px-4 py-2 border border-blue-500 text-blue-500 rounded-r-md hover:bg-blue-500 hover:text-black"
          >
            Send
          </button>
        </div>
      </div>
    </div>
  );
}

export default App;
