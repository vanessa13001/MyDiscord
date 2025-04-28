--
-- PostgreSQL database dump
--

-- Dumped from database version 17.4
-- Dumped by pg_dump version 17.4

-- Started on 2025-04-28 10:54:18

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 223 (class 1259 OID 16586)
-- Name: channel_memberships; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.channel_memberships (
    user_id integer NOT NULL,
    channel_id integer NOT NULL,
    role character varying(20) DEFAULT 'member'::character varying
);


ALTER TABLE public.channel_memberships OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 16542)
-- Name: channels; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.channels (
    id integer NOT NULL,
    name character varying(100) NOT NULL,
    is_private boolean DEFAULT false,
    members integer[],
    owner_id integer,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP
);


ALTER TABLE public.channels OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 16541)
-- Name: channels_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.channels_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.channels_id_seq OWNER TO postgres;

--
-- TOC entry 4894 (class 0 OID 0)
-- Dependencies: 219
-- Name: channels_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.channels_id_seq OWNED BY public.channels.id;


--
-- TOC entry 222 (class 1259 OID 16560)
-- Name: messages; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.messages (
    id integer NOT NULL,
    user_id integer,
    channel_id integer,
    content text,
    is_thread boolean DEFAULT false,
    parent_message_id integer,
    emoji_reactions jsonb,
    encrypted boolean DEFAULT false,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP
);


ALTER TABLE public.messages OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 16559)
-- Name: messages_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.messages_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.messages_id_seq OWNER TO postgres;

--
-- TOC entry 4895 (class 0 OID 0)
-- Dependencies: 221
-- Name: messages_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.messages_id_seq OWNED BY public.messages.id;


--
-- TOC entry 218 (class 1259 OID 16529)
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    id integer NOT NULL,
    first_name character varying(50),
    last_name character varying(50),
    email character varying(100) NOT NULL,
    password_hash text NOT NULL,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP,
    question_1 text,
    question_2 text
);


ALTER TABLE public.users OWNER TO postgres;

--
-- TOC entry 217 (class 1259 OID 16528)
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.users_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.users_id_seq OWNER TO postgres;

--
-- TOC entry 4896 (class 0 OID 0)
-- Dependencies: 217
-- Name: users_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.users_id_seq OWNED BY public.users.id;


--
-- TOC entry 4711 (class 2604 OID 16545)
-- Name: channels id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channels ALTER COLUMN id SET DEFAULT nextval('public.channels_id_seq'::regclass);


--
-- TOC entry 4714 (class 2604 OID 16563)
-- Name: messages id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages ALTER COLUMN id SET DEFAULT nextval('public.messages_id_seq'::regclass);


--
-- TOC entry 4709 (class 2604 OID 16532)
-- Name: users id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users ALTER COLUMN id SET DEFAULT nextval('public.users_id_seq'::regclass);


--
-- TOC entry 4888 (class 0 OID 16586)
-- Dependencies: 223
-- Data for Name: channel_memberships; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.channel_memberships (user_id, channel_id, role) FROM stdin;
\.


--
-- TOC entry 4885 (class 0 OID 16542)
-- Dependencies: 220
-- Data for Name: channels; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.channels (id, name, is_private, members, owner_id, created_at) FROM stdin;
1	general	f	{1,2,3,4}	1	2025-04-18 06:29:44.494529
2	staff	t	{1,2}	2	2025-04-18 06:29:44.494529
3	memes	f	{1,3,4}	3	2025-04-18 06:29:44.494529
\.


--
-- TOC entry 4887 (class 0 OID 16560)
-- Dependencies: 222
-- Data for Name: messages; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.messages (id, user_id, channel_id, content, is_thread, parent_message_id, emoji_reactions, encrypted, created_at) FROM stdin;
1	2	1	Thanks Alice! Happy to be here 😊	t	1	\N	f	2025-04-18 06:30:21.659687
2	1	2	Meeting starts at 3 PM. Don’t forget!	f	\N	\N	t	2025-04-18 06:30:21.659687
3	3	3	Check out this funny meme! 😂	f	\N	{"🔥": [1], "😂": [2, 4]}	f	2025-04-18 06:30:21.659687
\.


--
-- TOC entry 4883 (class 0 OID 16529)
-- Dependencies: 218
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.users (id, first_name, last_name, email, password_hash, created_at, question_1, question_2) FROM stdin;
1	Alice	Johnson	alice.johnson@example.com	hashed_pwd_1	2025-04-18 06:29:19.836302	Shrek	Balut
2	Elti	Smith	elti.smith@example.com	hashed_pwd_2	2025-04-18 06:29:19.836302	SpongeBob	Durian
3	Chris	Brown	chris.brown@example.com	hashed_pwd_3	2025-04-18 06:29:19.836302	Bugs	Haggis
4	Diana	Miller	diana.miller@example.com	hashed_pwd_4	2025-04-18 06:29:19.836302	Goofy	Escargot
5	Fiona	Davis	fiona.davis@example.com	hashed_pwd_6	2025-04-18 08:01:36.625345	Jerry	Tripe
7	Leila	Wilson	leila.wilson@example.com	hashed_pwd_8	2025-04-18 08:01:36.625345	Simba	Natto
8	Vanessa	Taylor	vanessa.taylor@example.com	hashed_pwd_9	2025-04-18 08:01:36.625345	Pikachu	Tofu
9	Julia	Moore	julia.moore@example.com	hashed_pwd_10	2025-04-18 08:01:36.625345	Tom	Insects
6	George	Evans	george.evans@example.com	hashed_pwd_7	2025-04-18 08:01:36.625345	Naruto	grenouille
10	Yuliia	Sherstiuk	yuliia.sherstiuk@laplateforme.io	zyx~}	2025-04-25 15:23:13.431333	Balto	Escargot
11	eltigani	Abdallah	eltigani.abdallah@laplateforme.io	)..;)$$;	2025-04-28 09:47:04.86208	mama bear	milkshake mangue
\.


--
-- TOC entry 4897 (class 0 OID 0)
-- Dependencies: 219
-- Name: channels_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.channels_id_seq', 3, true);


--
-- TOC entry 4898 (class 0 OID 0)
-- Dependencies: 221
-- Name: messages_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.messages_id_seq', 3, true);


--
-- TOC entry 4899 (class 0 OID 0)
-- Dependencies: 217
-- Name: users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.users_id_seq', 11, true);


--
-- TOC entry 4730 (class 2606 OID 16591)
-- Name: channel_memberships channel_memberships_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channel_memberships
    ADD CONSTRAINT channel_memberships_pkey PRIMARY KEY (user_id, channel_id);


--
-- TOC entry 4724 (class 2606 OID 16553)
-- Name: channels channels_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_name_key UNIQUE (name);


--
-- TOC entry 4726 (class 2606 OID 16551)
-- Name: channels channels_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_pkey PRIMARY KEY (id);


--
-- TOC entry 4728 (class 2606 OID 16570)
-- Name: messages messages_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_pkey PRIMARY KEY (id);


--
-- TOC entry 4720 (class 2606 OID 16540)
-- Name: users users_email_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_email_key UNIQUE (email);


--
-- TOC entry 4722 (class 2606 OID 16538)
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- TOC entry 4735 (class 2606 OID 16597)
-- Name: channel_memberships channel_memberships_channel_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channel_memberships
    ADD CONSTRAINT channel_memberships_channel_id_fkey FOREIGN KEY (channel_id) REFERENCES public.channels(id) ON DELETE CASCADE;


--
-- TOC entry 4736 (class 2606 OID 16592)
-- Name: channel_memberships channel_memberships_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channel_memberships
    ADD CONSTRAINT channel_memberships_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE CASCADE;


--
-- TOC entry 4731 (class 2606 OID 16554)
-- Name: channels channels_owner_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_owner_id_fkey FOREIGN KEY (owner_id) REFERENCES public.users(id) ON DELETE SET NULL;


--
-- TOC entry 4732 (class 2606 OID 16576)
-- Name: messages messages_channel_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_channel_id_fkey FOREIGN KEY (channel_id) REFERENCES public.channels(id) ON DELETE CASCADE;


--
-- TOC entry 4733 (class 2606 OID 16581)
-- Name: messages messages_parent_message_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_parent_message_id_fkey FOREIGN KEY (parent_message_id) REFERENCES public.messages(id) ON DELETE CASCADE;


--
-- TOC entry 4734 (class 2606 OID 16571)
-- Name: messages messages_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE SET NULL;


-- Completed on 2025-04-28 10:54:19

--
-- PostgreSQL database dump complete
--

