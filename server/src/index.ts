import { WebSocketServer,WebSocket } from "ws";
const wss= new WebSocketServer({port: 3000})
interface User {
    socket: WebSocket,
    room : string
}
let socketCollection :User[]= [];

wss.on("connection",(socket)=>{
    socket.on("message",(message:string)=>{  
        const parsedMessage= JSON.parse(message);
        if(parsedMessage.type == "join"){
           socketCollection.push({
            socket,
            room:parsedMessage.payload.roomId
        })
            console.log("someone join")
        }
        else{
            let currentRoomId:string= "";
            //search of roomId
            for(let i =0 ; i< socketCollection.length;i++){
                if(socketCollection[i].socket== socket){
                    currentRoomId=socketCollection[i].room;
                }
            }
            if(currentRoomId == ""){
                socket.send("not part of any room")
            }

            for(let i =0 ; i<socketCollection.length;i++){
                if(socketCollection[i].room== currentRoomId){
                    if(socketCollection[i].socket != socket){
                        socketCollection[i].socket.send(JSON.stringify(parsedMessage))
                    }
                }
            }

        }
    })
    socket.on("disconnect",()=>{
        socketCollection=socketCollection.filter(x=>x!)
    })
})